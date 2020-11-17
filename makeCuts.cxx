#include "MyMainFrame.h"
#include "TH2D.h"
#include <TLeaf.h>
#include "TFile.h"
#include "global.h"

void makeCuts(TBranch *eventn, TFile *outFile)
{
    Double_t tdcdiff, ToT_1, ToT_2;

    //Calculating the step size over (tdc2-tdc1)/2
    Double_t step = (right_max-left_max)/280.;

    hist_tdcdiff_with_cuts = new TH1D("tdcdiff_with_cuts","(tdc1-tdc2)/2 with cuts",2400, -12, 12);

    hist_tdcdiff_with_cuts->GetXaxis()->SetTitle("(tdc1-tdc2)/2 (ns)");
    hist_tdcdiff_with_cuts->GetXaxis()->SetTitleSize(0.06);
    hist_tdcdiff_with_cuts->GetXaxis()->SetTitleOffset(0.7);
  //  hist_tdcdiff_with_cuts->SetLineColor(kGreen);

    //Loop over all events in 't20'
    for (Int_t i=0; i<eventn->GetEntries(); i++)
    {

        eventn->GetEntry(i); //Getting the entery number 'i'

        ToT_1 = eventn->GetLeaf("adc1")->GetValue();
        ToT_2 = eventn->GetLeaf("adc2")->GetValue();

        tdcdiff=(eventn->GetLeaf("tdc1")->GetValue()-eventn->GetLeaf("tdc2")->GetValue())/2.;

	      Int_t j = int((tdcdiff - left_max+step/2.)/step);
	      if ((tdcdiff > left_max)&&(tdcdiff < left_max+step/2.)) j=0;
	      if ((tdcdiff > right_max-step/2.)&&(tdcdiff < right_max)) j=278; //279


        if ((j>0)&&(j<279)) {  //	 if ((j>0)&&(j<279)) {

        if ((ToT_1>ToT_1_cut[j])&&(ToT_2>ToT_2_cut[j])) {
                                                             // the peaks are supposed to be distributed by gauss
    //    if ((ToT_1<ToT_1_peak[j]+(ToT_1_peak[j]-ToT_1_cut[j]))&&(ToT_2<ToT_2_peak[j]+(ToT_2_peak[j]-ToT_2_cut[j]))) {

        hist_tdcdiff_with_cuts->Fill(tdcdiff);

                                                                                                                //    };
                                                        };
                            };


        if ((tdcdiff < left_max)||(j==0)) {

        if (ToT_1 > ToT_1_cut[1]) { // &&(ToT_1 < ToT_1_peak[1]+(ToT_1_peak[1]-ToT_1_cut[1]))
        if (ToT_2 > ToT_2_cut[1]) { // &&(ToT_2 < ToT_2_peak[1]+(ToT_2_peak[1]-ToT_2_cut[1]))

        hist_tdcdiff_with_cuts->Fill(tdcdiff);

                                                                                           };
                                                                                           };
                                          };


        if ((tdcdiff > right_max)||(j==279)) {

        if (ToT_1 > ToT_1_cut[278]) { // &&(ToT_1 < ToT_1_peak[277]+(ToT_1_peak[277]-ToT_1_cut[277]))
        if (ToT_2 > ToT_2_cut[278]) { // &&(ToT_2 < ToT_2_peak[277]+(ToT_2_peak[277]-ToT_2_cut[277]))

        hist_tdcdiff_with_cuts->Fill(tdcdiff);

                                                                                                   };
                                                                                                   };
                                             };

    }; // End of events loop

    MyMainFrame a;
    macro b;

    //Smoothing 'hist_tdcdiff_with_cuts'
    TH1 *hist_tdcdiff_with_cuts_smooth = a.Smooth_fun(hist_tdcdiff_with_cuts,180);

    hist_tdcdiff_with_cuts_smooth->GetXaxis()->SetTitle("(tdc1-tdc2)/2 (ns)");
    hist_tdcdiff_with_cuts_smooth->GetXaxis()->SetTitleSize(0.06);
    hist_tdcdiff_with_cuts_smooth->GetXaxis()->SetTitleOffset(0.7);
    hist_tdcdiff_with_cuts_smooth->SetName("tdcdiff_with_cuts_smooth");
    hist_tdcdiff_with_cuts_smooth->SetTitle("(tdc1-tdc2)/2 with cuts smooth");
    hist_tdcdiff_with_cuts_smooth->SetEntries(hist_tdcdiff_with_cuts->Integral(1,2400));

    //Getting the left and right boundary for tdcdiff with cuts
    Double_t left_max_cut = a.GetTDCleftcut(hist_tdcdiff_with_cuts_smooth);
    Double_t right_max_cut = a.GetTDCrightcut(hist_tdcdiff_with_cuts_smooth);

    //Printing on the screen effective speed of light in percentage (the second case)
    std::cout << "c_eff_with_cuts = " << 140./(right_max_cut-left_max_cut)/29.9792 << std::endl;


    outFile->mkdir("TDC_diff_after_cuts");
    outFile->cd("TDC_diff_after_cuts");

    TMacro *tdcdiffcut_1,*tdcdiffcut_smooth_1;

    tdcdiffcut_1 = b.TDC_plot("tdcdiff_with_cuts",left_max_cut,right_max_cut,hist_tdcdiff_with_cuts->GetMaximum());
    tdcdiffcut_smooth_1 = b.TDC_plot("tdcdiff_with_cuts_smooth",left_max_cut,right_max_cut,hist_tdcdiff_with_cuts_smooth->GetMaximum());


    hist_tdcdiff_with_cuts->Write();
    hist_tdcdiff_with_cuts_smooth->Write();

    tdcdiffcut_1->Write();
    tdcdiffcut_smooth_1->Write();

    tdcdiffcut_1->Delete();
    tdcdiffcut_smooth_1->Delete();
}
