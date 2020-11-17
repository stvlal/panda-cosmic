#include <TSpectrum.h>
#include "TH1D.h"
#include "TH2D.h"
#include <TError.h>
#include "MyMainFrame.h"
#include "global.h"
#include <TLeaf.h>
#include "TMacro.h"
#include "TFile.h"

void findPeaksCutsOffsets(TFile *outFile)
{
    //Declaring number of maxima to be found
    Int_t nfound_ToT_1;
    Int_t nfound_ToT_2;

    TSpectrum *s_ToT_1 = new TSpectrum(3);
    TSpectrum *s_ToT_2 = new TSpectrum(3);

    //Declaring the pointers to the arrays with x-positions of maxima
    Double_t *xpeaks_ToT_1;
    Double_t *xpeaks_ToT_2;

    gErrorIgnoreLevel = kError;

    //Loop over the bins
    for (Int_t j=0; j<280; j++)
    {
        //Searching for ToT's maxima
        nfound_ToT_1 = s_ToT_1->Search(hist_ToT_1_smooth[j] ,0 ,"new goff nodraw",0.2); // 0.1
        nfound_ToT_2 = s_ToT_2->Search(hist_ToT_2_smooth[j] ,0 ,"new goff nodraw",0.2);  // 0.1


        //Getting the array with x-positions of ToT_1's maxima
        xpeaks_ToT_1 = s_ToT_1->GetPositionX();

        //Setting the offset and peak for ToT_1 to the x-positions of the maximum zero
        ToT_1_offset[j] = xpeaks_ToT_1[0];
        ToT_1_peak[j] = xpeaks_ToT_1[0];

        //Getting the array with x-positions of ToT_2's maxima
        xpeaks_ToT_2 = s_ToT_2->GetPositionX();

        //Setting the offset and peak for ToT_2 to the x-positions of the maximum zero
        ToT_2_offset[j] = xpeaks_ToT_2[0];
        ToT_2_peak[j] = xpeaks_ToT_2[0];


            for (Int_t k=1; k<nfound_ToT_1; k++) { //Setting the offset of ToT_1 to the lowest x-peak position

                if (ToT_1_offset[j]>xpeaks_ToT_1[k]) ToT_1_offset[j] = xpeaks_ToT_1[k];

                                                 };

            for (Int_t k=0; k<nfound_ToT_1; k++) { //Setting ToT_1_peak[j] to the x-position of the peak that greater then offset

                if (xpeaks_ToT_1[k]>ToT_1_offset[j])ToT_1_peak[j] = xpeaks_ToT_1[k];

                                                 };

            for (Int_t k=0; k<nfound_ToT_1; k++) { //Making sure that ToT_1_peak[j] is the maximal x-position of the peak

                if (xpeaks_ToT_1[k]>ToT_1_offset[j]) {

                if (xpeaks_ToT_1[k]>ToT_1_peak[j])ToT_1_peak[j]=xpeaks_ToT_1[k];

                                                      };
                                                 };



            for (Int_t k=1; k<nfound_ToT_2; k++) { //Setting the offset of ToT_2 to the lowest x-peak position

                if (ToT_2_offset[j]>xpeaks_ToT_2[k]) ToT_2_offset[j] = xpeaks_ToT_2[k];

                                                 };

            for (Int_t k=0; k<nfound_ToT_2; k++) { //Setting ToT_2_peak[j] to the x-position of the peak that greater then offset

                if (xpeaks_ToT_2[k]>ToT_2_offset[j])ToT_2_peak[j] = xpeaks_ToT_2[k];

                                                 };

            for (Int_t k=0; k<nfound_ToT_2; k++) { //Making sure that ToT_2_peak[j] is the maximal x-position of the peak

                if (xpeaks_ToT_2[k]>ToT_2_offset[j]) {

                if (xpeaks_ToT_2[k]>ToT_2_peak[j])ToT_2_peak[j]=xpeaks_ToT_2[k];

                                                     };
                                                 };

    }; //End of loop over the bins ('j')


    gErrorIgnoreLevel = kWarning;


    for (Int_t j=0; j<280; j++) { //Loop of the bins

        //Setting range for x of hist_ToT_1_smooth[j] from offset to peak
        hist_ToT_1_smooth[j]->GetXaxis()->SetRange(hist_ToT_1_smooth[j]->FindBin(ToT_1_offset[j]),hist_ToT_1_smooth[j]->FindBin(ToT_1_peak[j]));

        //Setting ToT_1_cut[j] to the x-position of the minimum bin within the range
        ToT_1_cut[j] = hist_ToT_1_smooth[j]->GetBinCenter(hist_ToT_1_smooth[j]->GetMinimumBin());


        //Setting range for x of hist_ToT_2_smooth[j] from offset to peak
        hist_ToT_2_smooth[j]->GetXaxis()->SetRange(hist_ToT_2_smooth[j]->FindBin(ToT_2_offset[j]),hist_ToT_2_smooth[j]->FindBin(ToT_2_peak[j]));

        //Setting ToT_2_cut[j] to the x-position of the minimum bin within the range
        ToT_2_cut[j] = hist_ToT_2_smooth[j]->GetBinCenter(hist_ToT_2_smooth[j]->GetMinimumBin());

                                }; //End of loop over the bins


    TMacro *adcmacro;
    macro macros;

    outFile->cd("ToT_1");

    for (Int_t j=0; j<280; j++) {
        qqq << "ToT_1_" << j;
        adcmacro = macros.ADC_plot(qqq.str().c_str(),ToT_1_offset[j],ToT_1_peak[j],hist_ToT_1[j]->GetMaximum(),ToT_1_cut[j]);
        qqq.str("");
        adcmacro->Write();
        adcmacro->Delete();
                                };


    outFile->cd("ToT_2");

    for (Int_t j=0; j<280; j++) {
        qqq << "ToT_2_" << j;
        adcmacro = macros.ADC_plot(qqq.str().c_str(),ToT_2_offset[j],ToT_2_peak[j],hist_ToT_2[j]->GetMaximum(),ToT_2_cut[j]);
        qqq.str("");
        adcmacro->Write();
        adcmacro->Delete();
                                };

}
