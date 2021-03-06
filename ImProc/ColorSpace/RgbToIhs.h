/*
 * The information in this file is
 * subject to the terms and conditions of the
 * GNU Lesser General Public License Version 2.1
 * The license text is available from   
 * http://www.gnu.org/licenses/lgpl.html
 */

#ifndef RGBTOIHS_H__
#define RGBTOIHS_H__

#include "ColorSpaceConversionShell.h"

class RgbToIhs : public ColorSpaceConversionShell
{
public:
   RgbToIhs();
   virtual ~RgbToIhs();

   virtual bool getInputSpecification(PlugInArgList*& pInArgList);
   virtual void colorspaceConvert(double pOutput[3], double pInput[3], double maxComponent, double minComponent);

protected:
   virtual bool extractInputArgs(PlugInArgList* pInArgList);

private:
   bool mNormalizeHue;
};

#endif
