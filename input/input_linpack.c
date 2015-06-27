#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <stdlib.h>


static float atime[9][15];
static char this_month;
static int this_year;

void print_time (int row);
void matgen (float a[], int lda, int n, float b[], float *norma);
void dgefa (float a[], int lda, int n, int ipvt[], int *info);
void dgesl (float a[],int lda,int n,int ipvt[],float b[],int job);
void dmxpy (int n1, float y[], int n2, int ldm, float x[], float m[]);
void daxpy (int n, float da, float dx[], int incx, float dy[], int incy);
float epslon (float x);
int idamax (int n, float dx[], int incx);
void dscal (int n, float da, float dx[], int incx);
float ddot (int n, float dx[], int incx, float dy[], int incy);

/* TIME TIME TIME TIME TIME TIME TIME TIME TIME TIME TIME TIME TIME */
   #include <time.h>  /* for following time functions only */
   float second()
     {        
        float secs;
        clock_t Time;
        Time = clock();
        secs = (float)Time / (float)CLOCKS_PER_SEC;
        return secs ;
     }

/* DATE DATE DATE DATE DATE DATE DATE DATE DATE DATE DATE DATE DATE */
   #include <dos.h>   /* for following date functions only */
   void what_date()
     {
         /*   Watcom   */         
         struct dosdate_t adate;
         _dos_getdate( &adate );
         this_month = adate.month;
         this_year = adate.year;
         
         /*   Borland
         struct date adate;
         getdate( &adate );
         this_month = adate.da_mon;
         this_year = adate.da_year;
         */         
         return;
     }


main ()
{
        static float aa[200*200],a[200*201],b[200],x[200];       
        float cray,ops,total,norma,normx;
        float resid,residn,eps,t1,tm2,epsn,x1,x2;
        float mflops;
        static int ipvt[200],n,i,j,ntimes,info,lda,ldaa;
        int Endit, pass, loop;
        float overhead1, overhead2, time1, time2;
        FILE    *outfile;
        char *compiler, *options, general[9][80] = {" "}; 
         
        outfile = fopen("Linpack.txt","a+");
        if (outfile == NULL)
        {
            printf ("Cannot open results file \n\n");
            printf("Press any key\n");
            Endit = getch();
            exit (0);
        }

/************************************************************************
 *           Enter details of compiler and options used                 *
 ************************************************************************/
                  /*----------------- --------- --------- ---------*/
        compiler = "INSERT COMPILER NAME HERE";
        options  = "INSERT OPTIMISATION OPTIONS HERE";
                  /* Include -dDP or -dSP and -dROLL or -dUNROLL */
    
        lda = 201;
        ldaa = 200;
        cray = .056; 
        n = 100;

        fprintf(stdout,"Rolled ");fprintf(stdout,"Single");
        fprintf(stdout,"Precision Linpack Benchmark - PC Version in 'C/C++'\n\n");
        fprintf(stdout,"Compiler     %s\n",compiler);
        fprintf(stdout,"Optimisation %s\n\n",options);

        ops = (2.0e0*(n*n*n))/3.0 + 2.0*(n*n);

        matgen(a,lda,n,b,&norma);
        t1 = second();
        dgefa(a,lda,n,ipvt,&info);
        atime[0][0] = second() - t1;
        t1 = second();
        dgesl(a,lda,n,ipvt,b,0);
        atime[1][0] = second() - t1;
        total = atime[0][0] + atime[1][0];

/*     compute a residual to verify results.  */ 
        
        for (i = 0; i < 100; i++) {
                x[i] = b[i];
        }
        
        matgen(a,lda,n,b,&norma);
        // PARALLELIZE IN CUDA START
        for (i = 0; i < 100; i++) {
                b[i] = -b[i];
        }
        // PARALLELIZE IN CUDA END
        
        dmxpy(n,b,n,lda,x,a);
        resid = 0.0;
        normx = 0.0;
        for (i = 0; i < n; i++) {
                resid = (resid > fabs((double)b[i])) 
                        ? resid : fabs((double)b[i]);
                normx = (normx > fabs((double)x[i])) 
                        ? normx : fabs((double)x[i]);
        }
        eps = epslon(1.0);
        residn = resid/( n*norma*normx*eps );
        epsn = eps;
        x1 = x[0] - 1;
        x2 = x[n-1] - 1;
        
        printf("norm resid      resid           machep");
        printf("         x[0]-1          x[n-1]-1\n");
        printf("%6.1f %17.8e%17.8e%17.8e%17.8e\n\n",
               (double)residn, (double)resid, (double)epsn, 
               (double)x1, (double)x2);

        fprintf(stderr,"Times are reported for matrices of order        %5d\n",n);
        fprintf(stderr,"1 pass times for array with leading dimension of%5d\n\n",lda);
        fprintf(stderr,"      dgefa      dgesl      total     Mflops       unit");
        fprintf(stderr,"      ratio\n");

        atime[2][0] = total;
        if (total > 0.0)
        {
            atime[3][0] = ops/(1.0e6*total);
            atime[4][0] = 2.0/atime[3][0];
        }
        else
        {
            atime[3][0] = 0.0;
            atime[4][0] = 0.0;
        }
        atime[5][0] = total/cray;
       
        print_time(0);

/************************************************************************
 *       Calculate overhead of executing matgen procedure              *
 ************************************************************************/
       
        fprintf (stderr,"\nCalculating matgen overhead\n");
        pass = -20;
        loop = 10;
        do
        {
            time1 = second();
            pass = pass + 1;        
            for ( i = 0 ; i < loop ; i++)
            {
                 matgen(a,lda,n,b,&norma);
            }
            time2 = second();
            overhead1 = (time2 - time1);
            fprintf (stderr,"%10d times %6.2f seconds\n", loop, overhead1);
            if (overhead1 > 5.0)
            {
                pass = 0;
            }
            if (pass < 0)
            {
                if (overhead1 < 0.1)
                {
                    loop = loop * 10;
                }
                else
                {
                    loop = loop * 2;
                }
            }
        }
        while (pass < 0);
        
        overhead1 = overhead1 / (double)loop;

        fprintf (stderr,"Overhead for 1 matgen %12.5f seconds\n\n", overhead1);

/************************************************************************
 *           Calculate matgen/dgefa passes for 5 seconds                *
 ************************************************************************/
       
        fprintf (stderr,"Calculating matgen/dgefa passes for 5 seconds\n");
        pass = -20;
        ntimes = 10;
        do
        {
            time1 = second();
            pass = pass + 1;        
            for ( i = 0 ; i < ntimes ; i++)
            {
                matgen(a,lda,n,b,&norma);
                dgefa(a,lda,n,ipvt,&info );
            }
            time2 = second() - time1;
            fprintf (stderr,"%10d times %6.2f seconds\n", ntimes, time2);
            if (time2 > 5.0)
            {
                pass = 0;
            }
            if (pass < 0)
            {
                if (time2 < 0.1)
                {
                    ntimes = ntimes * 10;
                }
                else
                {
                    ntimes = ntimes * 2;
                }
            }
        }
        while (pass < 0);
        
        ntimes =  5.0 * (double)ntimes / time2;
        if (ntimes == 0) ntimes = 1;

        fprintf (stderr,"Passes used %10d \n\n", ntimes);
        fprintf(stderr,"Times for array with leading dimension of%4d\n\n",lda);
        fprintf(stderr,"      dgefa      dgesl      total     Mflops       unit");
        fprintf(stderr,"      ratio\n");        

/************************************************************************
 *                              Execute 5 passes                        *
 ************************************************************************/
      
        tm2 = ntimes * overhead1;
        atime[3][6] = 0;

        for (j=1 ; j<6 ; j++)
        {
        
            t1 = second();

            for (i = 0; i < ntimes; i++)
            {
                matgen(a,lda,n,b,&norma);
                dgefa(a,lda,n,ipvt,&info );
            }

            atime[0][j] = (second() - t1 - tm2)/ntimes;

            t1 = second();      
        
            for (i = 0; i < ntimes; i++)
            {
                dgesl(a,lda,n,ipvt,b,0);
            }

            atime[1][j] = (second() - t1)/ntimes;
            total       = atime[0][j] + atime[1][j];
            atime[2][j] = total;
            atime[3][j] = ops/(1.0e6*total);
            atime[4][j] = 2.0/atime[3][j];
            atime[5][j] = total/cray;
            atime[3][6] = atime[3][6] + atime[3][j];
            
            print_time(j);
        }
        atime[3][6] = atime[3][6] / 5.0;
        fprintf (stderr,"Average                          %11.2f\n",
                                               (double)atime[3][6]);        
        
        fprintf (stderr,"\nCalculating matgen2 overhead\n");

/************************************************************************
 *             Calculate overhead of executing matgen procedure         *
 ************************************************************************/

        time1 = second();        
        for ( i = 0 ; i < loop ; i++)
        {
            matgen(aa,ldaa,n,b,&norma);    
        }
        time2 = second();
        overhead2 = (time2 - time1);
        overhead2 = overhead2 / (double)loop;
        
        fprintf (stderr,"Overhead for 1 matgen %12.5f seconds\n\n", overhead2);
        fprintf(stderr,"Times for array with leading dimension of%4d\n\n",ldaa);
        fprintf(stderr,"      dgefa      dgesl      total     Mflops       unit");
        fprintf(stderr,"      ratio\n");

/************************************************************************
 *                              Execute 5 passes                        *
 ************************************************************************/
              
        tm2 = ntimes * overhead2;
        atime[3][12] = 0;

        for (j=7 ; j<12 ; j++)
        {
        
            t1 = second();

            for (i = 0; i < ntimes; i++)
            {
                matgen(aa,ldaa,n,b,&norma);
                dgefa(aa,ldaa,n,ipvt,&info  );
            }

            atime[0][j] = (second() - t1 - tm2)/ntimes;

            t1 = second();      
        
            for (i = 0; i < ntimes; i++)
            {
                dgesl(aa,ldaa,n,ipvt,b,0);
            }

            atime[1][j] = (second() - t1)/ntimes;
            total       = atime[0][j] + atime[1][j];
            atime[2][j] = total;
            atime[3][j] = ops/(1.0e6*total);
            atime[4][j] = 2.0/atime[3][j];
            atime[5][j] = total/cray;
            atime[3][12] = atime[3][12] + atime[3][j];

            print_time(j);
        }
        atime[3][12] = atime[3][12] / 5.0; 
        fprintf (stderr,"Average                          %11.2f\n",
                                              (double)atime[3][12]);  

/************************************************************************
 *           Use minimum average as overall Mflops rating               *
 ************************************************************************/
      
        mflops = atime[3][6];
        if (atime[3][12] < mflops) mflops = atime[3][12];
       
        fprintf(stderr,"\n");
        fprintf(stderr,ROLLING);fprintf(stderr,"Single");
        fprintf(stderr," Precision %11.2f Mflops \n\n",mflops);

        what_date();

/************************************************************************
 *             Type details of hardware, software etc.                  *
 ************************************************************************/

    printf ("Enter the following data which will be "
                                "appended to file Linpack.txt \n\n");
    printf ("PC Supplier/model ?\n                    ");
    scanf ("%[^\n]", general[1]);
    fflush (stdin);
    printf ("CPU               ?\n                    ");
    scanf ("%[^\n]", general[2]);
    fflush (stdin);
    printf ("Clock MHz         ?\n                    ");
    scanf ("%[^\n]", general[3]);
    fflush (stdin);
    printf ("Cache             ?\n                    ");
    scanf ("%[^\n]", general[4]);
    fflush (stdin);
    printf ("Chipset/options   ?\n                    ");
    scanf ("%[^\n]", general[5]);
    fflush (stdin);
    printf ("OS/DOS version    ?\n                    ");
    scanf ("%[^\n]", general[6]);
    fflush (stdin);
    printf ("Your name         ?\n                    ");
    scanf ("%[^\n]", general[7]);
    fflush (stdin);
    printf ("Where from        ?\n                    ");
    scanf ("%[^\n]", general[8]);
    fflush (stdin);
    printf ("Mail address      ?\n                    ");
    scanf ("%[^\n]", general[0]);
    fflush (stdin);

/************************************************************************
 *              Add results to output file LLloops.txt                  *
 ************************************************************************/
            
    fprintf (outfile, "----------------- ----------------- --------- "
                      "--------- ---------\n");
    fprintf (outfile, "LINPACK BENCHMARK FOR PCs 'C/C++'    n @ 100\n\n");
    fprintf (outfile, "Month run         %d/%d\n", this_month, this_year);
    fprintf (outfile, "PC model          %s\n", general[1]);
    fprintf (outfile, "CPU               %s\n", general[2]);
    fprintf (outfile, "Clock MHz         %s\n", general[3]);
    fprintf (outfile, "Cache             %s\n", general[4]);
    fprintf (outfile, "Options           %s\n", general[5]);
    fprintf (outfile, "OS/DOS            %s\n", general[6]);
    fprintf (outfile, "Compiler          %s\n", compiler);
    fprintf (outfile, "OptLevel          %s\n", options);
    fprintf (outfile, "Run by            %s\n", general[7]);
    fprintf (outfile, "From              %s\n", general[8]);
    fprintf (outfile, "Mail              %s\n\n", general[0]);
    
    fprintf(outfile, "Rolling            %s\n","Rolled ");
    fprintf(outfile, "Precision          %s\n","Single"); 
    fprintf(outfile, "norm. resid        %16.1f\n",(double)residn);
    fprintf(outfile, "resid              %16.8e\n",(double)resid);
    fprintf(outfile, "machep             %16.8e\n",(double)epsn);
    fprintf(outfile, "x[0]-1             %16.8e\n",(double)x1);
    fprintf(outfile, "x[n-1]-1           %16.8e\n",(double)x2);
    fprintf(outfile, "matgen 1 seconds   %16.5f\n",overhead1);
    fprintf(outfile, "matgen 2 seconds   %16.5f\n",overhead2); 
    fprintf(outfile, "Repetitions        %16d\n",ntimes);
    fprintf(outfile, "Leading dimension  %16d\n",lda);  
    fprintf(outfile, "                              dgefa     dgesl "
                     "    total    Mflops\n");
    fprintf(outfile, "1 pass seconds     %16.5f %9.5f %9.5f\n",
                      atime[0][0], atime[1][0], atime[2][0]);
                      
    for (i=1 ; i<6 ; i++)
    {                 
        fprintf(outfile, "Repeat seconds     %16.5f %9.5f %9.5f %9.2f\n",                
                       atime[0][i], atime[1][i], atime[2][i], atime[3][i]);
    }
    fprintf(outfile, "Average            %46.2f\n",atime[3][6]);
    
    fprintf(outfile, "Leading dimension  %16d\n",ldaa);
     
    for (i=7 ; i<12 ; i++)
    {                 
        fprintf(outfile, "Repeat seconds     %16.5f %9.5f %9.5f %9.2f\n",                
                       atime[0][i], atime[1][i], atime[2][i], atime[3][i]);
    }
    fprintf(outfile, "Average            %46.2f\n\n",atime[3][12]); 
    
    fclose (outfile);
    
    printf("\nPress any key\n");
    Endit = getch();
}
void print_time (int row)

{
fprintf(stderr,"%11.5f%11.5f%11.5f%11.2f%11.4f%11.4f\n",   (double)atime[0][row],
       (double)atime[1][row], (double)atime[2][row], (double)atime[3][row], 
       
       (double)atime[4][row], (double)atime[5][row]);
       return;
}
void matgen (float a[], int lda, int n, float b[], float *norma)


/* We would like to declare a[][lda], but c does not allow it.  In this
function, references to a[i][j] are written a[lda*i+j].  */

{
       

        init = 1325;
        *norma = 0.0;
        
        
        
        return;
}

