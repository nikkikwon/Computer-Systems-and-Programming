#include "functions.h"

/*Introduction paragraph: This program contains several subroutines which will be called by the main
function. Depending on the command user types in, different tasks of image processing will be done. 
After processing the image, the output image will be saved to see the changes from the original image. 
Some of these subroutines depend on other subroutines, which is achieved through nested subroutine call.*/

/*
 * getRadius - returns the radius based on the sigma value
 * INPUTS: sigma - sigma in the Guassian distribution
 * OUTPUTS: none
 * RETURN VALUE: radius - radius of the filter
 */
int getRadius(double sigma)
{
  /*Write your function here*/
  int radius;

  radius = ceil(3*sigma); 

  return radius;
}

/*
 * calculateGausFilter - calculates the Gaussian filter
 * INTPUTS: gausFitler - pointer to the array for the gaussian filter
 *          sigma - the sigma in the Gaussian distribution
 * OUTPUTS: none
 * RETURN VALUE: none
 */
void calculateGausFilter(double *gausFilter,double sigma)
{
  /*Write your function here*/
 
  int radius;
  int x, y;
  int i=0; 
  double weight=0.0;
   
  /*loop for every values of x,y and put outcome into corresponding filter array*/
  radius=getRadius(sigma);   	
  for (y=radius; y>=-radius; y--)
  {
    for (x=-radius; x<=radius; x++)
    {
        *(gausFilter + i) = ( 1 / sqrt(2*M_PI*sigma*sigma) ) * exp (-(  (x*x+y*y)/(2*sigma*sigma) ));
        i=i+1; 
    }    

  }
  /*weight=all the values in the filter array added together*/
  for (i=0; i<((radius*2+1)*(radius*2+1)); i++)
  {
    weight+= *(gausFilter + i);
  }
  /*Make it so that when all values in filter array is added it becomes one*/
  for (i=0; i<((radius*2+1)*(radius*2+1)); i++)
  {
    *(gausFilter+i) = *(gausFilter+i)/weight;
  }
  return;
}

/* convolveImage - performs a convolution between a filter and image
 * INPUTS: inRed - pointer to the input red channel
 *         inGreen - pointer to the input green channel
 *         inBlue - pointer to the input blue channel
 *         inAlpha - pointer to the input alpha channel
 *         filter - pointer to the convolution filter
 *         radius - radius of the convolution filter
 *         width - width of the input image
 *         height - height of the input image
 * OUTPUTS: outRed - pointer to the output red channel
 *          outGreen - pointer to the output green channel
 *          outBlue - pointer to the output blue channel
 *          outAlpha - pointer to the output alpha channel
 * RETURN VALUES: none
 */
void convolveImage(uint8_t *inRed,uint8_t *inGreen,uint8_t *inBlue,
                   uint8_t *inAlpha, uint8_t *outRed,uint8_t *outGreen,
                   uint8_t *outBlue,uint8_t *outAlpha,const double *filter,
                   int radius,int width,int height)
{
  /*Write your function here*/
  double sum_r=0.0;
  double sum_g=0.0;
  double sum_b=0.0; 
  int row,col; 
  int i, j;
  double r,g,b;
  // if value of radius less than 1, just copy in values into out values. Leave it unchanged. 
  if (radius<1)
  {
    for (i=0; i<(height*width); i++)
    {
      *(outRed+i)=*(inRed+i);	
    }

    for (i=0; i<(height*width); i++)
    {
      *(outGreen+i)=*(inGreen+i);	
    }

    for (i=0; i<(height*width); i++)
    {
      *(outBlue+i)=*(inBlue+i);	
    }

     for (i=0; i<(height*width); i++)
    {
      *(outAlpha+i)=*(inAlpha+i);	
    }
  return;	
  }

  // for every pixels in the image, apply filter by multiplying all the near values with the image itself. Exclude unincluded parts. 
  for (row = 0; row < height; row++)
  {
    for (col = 0; col < width; col++)
    {
      sum_r=0;
      sum_g=0;
      sum_b=0;
  
      for (i = 0; i < (radius*2)+1 ; i++)
      {
        for (j = 0; i < (radius*2)+1; j++)
	  {

            if((row-radius+i) < 0  &&  (row-radius+i) <= height &&  (col-radius+j) <0 && (col-radius+j) <= width )
	      ; // if out of image boundary do not modified sums initialized to zero
	    else
	    {
	      r=*(filter+(i*(radius*2+1)+j)) * *(inRed +(row*width+col));
	      g=*(filter+(i*(radius*2+1)+j)) * *(inGreen +(row*width+col));
	      b=*(filter+(i*(radius*2+1)+j)) * *(inBlue +(row*width+col));
	
              //0-255 boundary check
  	      if (r<0)
	        r=0;
	      else if (r>255)
		r=255;

	      if (g<0)
	        g=0;
	      else if (g>255)
		g=255;

	      if (b<0)
	        b=0;
	      else if (b>255)
		b=255;

	      sum_r= sum_r+r;
	      sum_g= sum_g+g;
              sum_b= sum_b+b;
	    }
				
	  }

      }      
 
    
    /*leave Alpha channel unchanged, just copy from in to out*/
    for (i=0; i<(height*width); i++)
    {
      *(outAlpha+i)=*(inAlpha+i);	
    }
	
    *(outRed+(row*width+col)) = sum_r;
    *(outGreen+(row*width+col)) = sum_g;
    *(outBlue+(row*width+col)) = sum_b;  
    }
  }


  return;
}

/* convertToGray - convert the input image to grayscale
 * INPUTS: inRed - pointer to the input red channel
 *         inGreen - pointer to the input green channel
 *         inBlue - pointer to the input blue channel
 *         inAlpha - pointer to the input alpha channel
 *         gMonoMult - pointer to array with constants to be multipiled with 
 *                     RBG channels to convert image to grayscale
 *         width - width of the input image
 *         height - height of the input image
 * OUTPUTS: outRed - pointer to the output red channel
 *          outGreen - pointer to the output green channel
 *          outBlue - pointer to the output blue channel
 *          outAlpha - pointer to the output alpha channel
 * RETURN VALUES: none
 */
void convertToGray(uint8_t *inRed,uint8_t *inGreen,uint8_t *inBlue,
                   uint8_t *inAlpha,uint8_t *outRed,uint8_t *outGreen,
                   uint8_t *outBlue,uint8_t *outAlpha,
                   const double *gMonoMult,int width,int height)
{
  /*Challenge- Write your function here*/
  int i;
  for (i=0; i < height*width; i++)
  {
     outRed[i] = gMonoMult[0]*inRed[i]+gMonoMult[1]*inGreen[i]+gMonoMult[2]*inBlue[i];
     outGreen[i] = outRed[i];
     outBlue[i]	= outRed[i];
     outAlpha[i]=inAlpha[i];
  }


  return;
}

/* invertImage - inverts the colors of the image
 * INPUTS: inRed - pointer to the input red channel
 *         inGreen - pointer to the input green channel
 *         inBlue - pointer to the input blue channel
 *         inAlpha - pointer to the input alpha channel
 *         width - width of the input image
 *         height - height of the input image
 * OUTPUTS: outRed - pointer to the output red channel
 *          outGreen - pointer to the output green channel
 *          outBlue - pointer to the output blue channel
 *          outAlpha - pointer to the output alpha channel
 * RETURN VALUES: none
 */
void invertImage(uint8_t *inRed,uint8_t *inGreen,uint8_t *inBlue,
                 uint8_t *inAlpha,uint8_t *outRed,uint8_t *outGreen,
                 uint8_t *outBlue,uint8_t *outAlpha,int width,int height)
{
  /*Challenge- Write your function here*/
  int i;

  for(i=0; i < (width*height); i++)
  {
    outRed[i] = 255-inRed[i];
    outGreen[i] = 255-inGreen[i];
    outBlue[i] = 255-inBlue[i];
    outAlpha[i]=inAlpha[i];
  }

  return;
}

/* pixelate - pixelates the image
 * INPUTS: inRed - pointer to the input red channel
 *         inGreen - pointer to the input green channel
 *         inBlue - pointer to the input blue channel
 *         inAlpha - pointer to the input alpha channel
 *         pixelateY - height of the block
 *         pixelateX - width of the block
 *         width - width of the input image
 *         height - height of the input image
 * OUTPUTS: outRed - pointer to the output red channel
 *          outGreen - pointer to the output green channel
 *          outBlue - pointer to the output blue channel
 *          outAlpha - pointer to the output alpha channel
 * RETURN VALUES: none
 */
void pixelate(uint8_t *inRed,uint8_t *inGreen,uint8_t *inBlue,uint8_t *inAlpha,
              uint8_t *outRed,uint8_t *outGreen,uint8_t *outBlue,
              uint8_t *outAlpha,int pixelY,int pixelX,int width,int height)
{
  /*Challenge- Write your function here*/
  return;
}

/* colorDodge - blends the bottom layer with the top layer
 * INPUTS: aRed - pointer to the bottom red channel
 *         aGreen - pointer to the bottom green channel
 *         aBlue - pointer to the bottom blue channel
 *         aAlpha - pointer to the bottom alpha channel
 *         bRed - pointer to the top red channel
 *         bGreen - pointer to the top green channel
 *         bBlue - pointer to the top blue channel
 *         bAlpha - pointer to the top alpha channel
 *         width - width of the input image
 *         height - height of the input image
 * OUTPUTS: outRed - pointer to the output red channel
 *          outGreen - pointer to the output green channel
 *          outBlue - pointer to the output blue channel
 *          outAlpha - pointer to the output alpha channel
 * RETURN VALUES: none
 */
void colorDodge(uint8_t *aRed,uint8_t *aGreen,uint8_t *aBlue,
                uint8_t *aAlpha,uint8_t *bRed,uint8_t *bGreen,
                uint8_t *bBlue,uint8_t *bAlpha,uint8_t *outRed,
                uint8_t *outGreen,uint8_t *outBlue,uint8_t *outAlpha,
                int width,int height)
{
   /*Challenge- Write your function here*/
   int i;
   for (i=0; i < width*height; i++)
   {
     outRed[i] = ( (bRed[i]==255) ? bRed[i] : min(((aRed[i]<<8)/(255-bRed[i])),255));

     outGreen[i] = ((bGreen[i]==255)?bGreen[i]:min(((aGreen[i]<<8)/(255-bGreen[i])),255));

     outBlue[i] = ((bBlue[i]==255)?bBlue[i]:min(((aBlue[i]<<8)/(255-bBlue[i])),255));

     outAlpha[i]=aAlpha[i];
   }

   return;
}

/* pencilSketch - creates a pencil sketch of the input image
 * INPUTS: inRed - pointer to the input red channel
 *         inGreen - pointer to the input green channel
 *         inBlue - pointer to the input blue channel
 *         inAlpha - pointer to the input alpha channel
 *         invRed - pointer to temporary red channel for inversion
 *         invGreen - pointer to temporary green channel for inversion
 *         invBlue - pointer to temporary blue channel for inversion
 *         invAlpha - pointer to temporary alpha channel for inversion
 *         blurRed - pointer to temporary red channel for blurring
 *         blurGreen - pointer to temporary green channel for blurring
 *         blurBlue - pointer to temporary blue channel for blurring
 *         blurAlpha - pointer to temporary alpha channel for blurring
 *         filter - pointer to the gaussian filter to blur the image
 *         radius - radius of the gaussian filter
 *         width - width of the input image
 *         height - height of the input image
 *         gMonoMult - pointer to array with constants to be multipiled with 
 *                     RBG channels to convert image to grayscale
 * OUTPUTS: outRed - pointer to the output red channel
 *          outGreen - pointer to the output green channel
 *          outBlue - pointer to the output blue channel
 *          outAlpha - pointer to the output alpha channel
 * RETURN VALUES: none
 */
void pencilSketch(uint8_t *inRed,uint8_t *inGreen,uint8_t *inBlue,
                  uint8_t *inAlpha,uint8_t *invRed,uint8_t *invGreen,
                  uint8_t *invBlue,uint8_t *invAlpha,uint8_t *blurRed,
                  uint8_t *blurGreen,uint8_t *blurBlue,uint8_t *blurAlpha,
                  uint8_t *outRed,uint8_t *outGreen,uint8_t *outBlue,
                  uint8_t *outAlpha,const double *filter,int radius,int width,
                  int height,const double *gMonoMult)
{
    /*Challenge- Write your function here*/
    return;
}

/* transformImage - Computes an linear transformation of the input image
 * INPUTS: inRed - pointer to the input red channel
 *         inGreen - pointer to the input green channel
 *         inBlue - pointer to the input blue channel
 *         inAlpha - pointer to the input alpha channel
 *	    transform - two dimensional array containing transform coefficients of matrix T and vector S
 *         width - width of the input and output image
 *         height - height of the input and output image
 * OUTPUTS: outRed - pointer to the output red channel
 *          outGreen - pointer to the output green channel
 *          outBlue - pointer to the output blue channel
 *          outAlpha - pointer to the output alpha channel
 * RETURN VALUES: none
 */
void transformImage(uint8_t *inRed,uint8_t *inGreen,uint8_t *inBlue,uint8_t *inAlpha,
              uint8_t *outRed,uint8_t *outGreen,uint8_t *outBlue,
              uint8_t *outAlpha,double transform[2][3],int width,int height)
{
     /*Write your function here*/
     int row, col;
     //int xtrans, ytrans;
     int xn, yn;

     for (row = 0; row < height; row++)
     {
       for (col=0; col < width; col++)
       {
	 //outpixels assigned the original pixel. 
	 inRed[row*width+col] = outRed[row*width+col];
	 inGreen[row*width+col] = outGreen[row*width+col];
 	 inBlue[row*width+col] = outBlue[row*width+col];

	 nearestPixel(row, col, transform, &yn, &xn, width, height );

	 //xtrans=transform[0][0]*row + transform[0][1]*col + transform[0][2];
	 //ytrans=transform[1][0]*row + transform[1][1]*col + transform[1][2];
	
       }     

     }	

     return;
}

/* nearestPixel - computes the inverse transform to find the closest pixel in the original image
 * INPUTS: pixelYtransform - row value in transformed image
 *         pixelXtransform - column value in transformed image
 *         transform - two dimensional array containing transform coefficients of matrix T and vector S
 *         width - width of the input and output image
 *         height - height of the input and output image
 * OUTPUTS: pixelY - pointer to row value in original image
 *	    pixelX - pointer to column value in original image
 * RETURN VALUES: none
 */
void nearestPixel(int pixelYTransform, int pixelXTransform, double transform[2][3],
              int *pixelY, int *pixelX, int width, int height)
{
     /*Write your function here*/
     int i;
     for (i=0; i< width*height; i++)
     {     
       pixelX[i]=(1/ ((transform[0][0]*transform[1][1])-(transform[0][1]*transform[1][0]))  ) * 
       ( ( transform[1][1]*(pixelXTransform - transform[0][2]) ) + (-(transform[1][0])*(pixelYTransform - transform[1][2])) );

       pixelY[i]=(1/ ((transform[0][0]*transform[1][1])-(transform[0][1]*transform[1][0]))  ) *
       ( ( transform[1][0]*(pixelXTransform - transform[0][2]) ) + (transform[0][0]*(pixelYTransform - transform[1][2])) );


     }  

     return;
}

