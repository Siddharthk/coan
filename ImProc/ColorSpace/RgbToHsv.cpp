/*
 * The information in this file is
 * subject to the terms and conditions of the
 * GNU Lesser General Public License Version 2.1
 * The license text is available from   
 * http://www.gnu.org/licenses/lgpl.html
 */

#include "AppVerify.h"
#include "ImProcVersion.h"
#include "PlugInArgList.h"
#include "PlugInRegistration.h"
#include "RgbToHsv.h"

REGISTER_PLUGIN_BASIC(ColorSpace, RgbToHsv);

#define EPSILON 0.000001

RgbToHsv::RgbToHsv() : mNormalizeHue(true)
{
   setName("RgbToHsv");
   setDescription("Convert between RGB and HSV.");
   setDescriptorId("{0DC474B1-A30A-42EC-B9D7-BBE12AF27695}");
   setMenuLocation("[General Algorithms]/Colorspace Conversion/RGB->HSV");
   setScaleData(true);
}

RgbToHsv::~RgbToHsv()
{
}

bool RgbToHsv::getInputSpecification(PlugInArgList*& pInArgList)
{
   if (!ColorSpaceConversionShell::getInputSpecification(pInArgList))
   {
      return false;
   }
   VERIFY(pInArgList->addArg<bool>("Normalize Hue", mNormalizeHue, std::string("Should the hue be normalized to (0,360]?")));
   return true;
}

bool RgbToHsv::extractInputArgs(PlugInArgList* pInArgList)
{
   if (!ColorSpaceConversionShell::extractInputArgs(pInArgList))
   {
      return false;
   }
   pInArgList->getPlugInArgValue("Normalize Hue", mNormalizeHue);
   return true;
}

void RgbToHsv::colorspaceConvert(double pOutput[3], double pInput[3], double maxComponent, double minComponent)
{
   double red = pInput[0];
   double green = pInput[1];
   double blue = pInput[2];
   double h = 0.0;
   double s = 0.0;
   double v = 0.0;
   if (fabs(maxComponent) < EPSILON)
   {
      pOutput[0] = pOutput[1] = pOutput[2] = 0.0;
      return;
   }

   // hue
   if (fabs(maxComponent - minComponent) < EPSILON)
   {
      h = 0;
   }
   else if (fabs(maxComponent - red) < EPSILON)
   {
      h = fmod(60 * (green - blue) / (maxComponent - minComponent), 360);
   }
   else if (fabs(maxComponent - green) < EPSILON)
   {
      h = 60 * (blue - red) / (maxComponent - minComponent) + 120;
   }
   else if (fabs(maxComponent - blue) < EPSILON)
   {
      h = 60 * (red - green) / (maxComponent - minComponent) + 240;
   }

   // saturation
   s = 1.0 - (minComponent / maxComponent);

   // value
   v = maxComponent;

   if (mNormalizeHue && h < 0.0)
   {
      h += 360.0;
   }
   pOutput[0] = h;
   pOutput[1] = s;
   pOutput[2] = v;
}
