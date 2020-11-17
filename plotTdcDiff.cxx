#include <iostream>
#include "TH1D.h"
#include <TLeaf.h>
#include "TH1.h"
#include "TH2D.h"
#include "global.h"
#include "MyMainFrame.h"
#include "TMacro.h"
#include "TFile.h"

void plotTdcDiff(TBranch *eventn, TFile *outFile)
{
    //Printing on the screen number of events in the branch 'eventn'
    std::cout << "N enteries = " << eventn->GetEntries() << "\n";

    hist_tdcdiff = new TH1D("tdcdiff","(tdc1-tdc2)/2",2400, -12, 12);

    hist_tdcdiff->GetXaxis()->SetTitle("(tdc1-tdc2)/2 (ns)");
    hist_tdcdiff->GetXaxis()->SetTitleSize(0.06);
    hist_tdcdiff->GetXaxis()->SetTitleOffset(0.7);


    TH1D *hist_tdcdiff_tot3 = new TH1D("tdcdiff_tot3","(tdc1-tdc2)/2",2400, -12, 12);

    hist_tdcdiff_tot3->GetXaxis()->SetTitle("(tdc1-tdc2)/2 (ns)");
    hist_tdcdiff_tot3->GetXaxis()->SetTitleSize(0.06);
    hist_tdcdiff_tot3->GetXaxis()->SetTitleOffset(0.7);


    TH1D *hist_diff_tdc3_tdc2 = new TH1D("tdc3_tdc2","tdc3-tdc2",280, -12, 5);

    hist_diff_tdc3_tdc2->GetXaxis()->SetTitle("tdc3-tdc2 (ns)");
    hist_diff_tdc3_tdc2->GetXaxis()->SetTitleSize(0.06);
    hist_diff_tdc3_tdc2->GetXaxis()->SetTitleOffset(0.7);


    TH1D *hist_diff_tdc3_tdc1 = new TH1D("tdc3_tdc1","tdc3-tdc1",280, -20, 5);

    hist_diff_tdc3_tdc1->GetXaxis()->SetTitle("tdc3-tdc1 (ns)");
    hist_diff_tdc3_tdc1->GetXaxis()->SetTitleSize(0.06);
    hist_diff_tdc3_tdc1->GetXaxis()->SetTitleOffset(0.7);

    for (Int_t i=0; i<eventn->GetEntries(); i++) //Loop over all events in 't20'
    {
        eventn->GetEntry(i); //Getting the entery number 'i'

        if (eventn->GetLeaf("adc1")->GetValue()>10.)
        {
        if (eventn->GetLeaf("adc2")->GetValue()>10.)
        {

        //Filling out the histogram 'hist_tdcdiff' with (tdc1-tdc2)/2
        hist_tdcdiff->Fill((eventn->GetLeaf("tdc1")->GetValue()-eventn->GetLeaf("tdc2")->GetValue())/2);

        hist_diff_tdc3_tdc2->Fill(eventn->GetLeaf("tdc0")->GetValue()-eventn->GetLeaf("tdc2")->GetValue());

        hist_diff_tdc3_tdc1->Fill(eventn->GetLeaf("tdc0")->GetValue()-eventn->GetLeaf("tdc1")->GetValue());

        if (eventn->GetLeaf("adc0")->GetValue()>0)
        {
            hist_tdcdiff_tot3->Fill((eventn->GetLeaf("tdc1")->GetValue()-eventn->GetLeaf("tdc2")->GetValue())/2);
        }

        }; //End of ToT_2 if
        }; //End of ToT_1 if

    }; // End of events loop



    MyMainFrame opa;
    macro macros;

    //Smoothing 'hist_tdcdiff'.
    hist_tdcdiff_smooth = opa.Smooth_fun(hist_tdcdiff,180);

    hist_tdcdiff_smooth->GetXaxis()->SetTitle("(tdc1-tdc2)/2 (ns)");
    hist_tdcdiff_smooth->GetXaxis()->SetTitleSize(0.06);
    hist_tdcdiff_smooth->GetXaxis()->SetTitleOffset(0.7);
    hist_tdcdiff_smooth->SetName("tdcdiff_smooth");
    hist_tdcdiff_smooth->SetTitle("(tdc1-tdc2)/2 smooth");

    //Getting the left and right boundary for tdcdiff
    left_max = opa.GetTDCleftcut(hist_tdcdiff_smooth);
    right_max = opa.GetTDCrightcut(hist_tdcdiff_smooth);

    //Printing on the screen effective speed of light in percentage
    std::cout << "c_eff_without_cuts = " << 140./(right_max-left_max)/29.9792 << std::endl;


    outFile->mkdir("TDC_diff");
    outFile->cd("TDC_diff");

    TMacro *tdcdiffcut,*tdcdiffcut_smooth;

    tdcdiffcut = macros.TDC_plot("tdcdiff",left_max,right_max,hist_tdcdiff->GetMaximum());
    tdcdiffcut_smooth = macros.TDC_plot("tdcdiff_smooth",left_max,right_max,hist_tdcdiff_smooth->GetMaximum());

    hist_tdcdiff->SetEntries(hist_tdcdiff->Integral(1,2400));
    hist_tdcdiff->Write();

    hist_tdcdiff_smooth->SetEntries(hist_tdcdiff->Integral(1,2400));
    hist_tdcdiff_smooth->Write();

    hist_tdcdiff_tot3->SetEntries(hist_tdcdiff_tot3->Integral(1,2400));
    hist_tdcdiff_tot3->Write();

    hist_diff_tdc3_tdc2->SetEntries(hist_diff_tdc3_tdc2->Integral(1,2400));
    hist_diff_tdc3_tdc2->Write();

    hist_diff_tdc3_tdc1->SetEntries(hist_diff_tdc3_tdc1->Integral(1,2400));
    hist_diff_tdc3_tdc1->Write();

    tdcdiffcut->Write();
    tdcdiffcut_smooth->Write();

    tdcdiffcut->Delete();
    tdcdiffcut_smooth->Delete();
}
