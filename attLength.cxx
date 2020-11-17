#include "TH1D.h"
#include <cmath>
#include "TMacro.h"
#include "TFile.h"
#include <TLeaf.h>
#include "TH2D.h"
#include "global.h"
#include "macro.h"

void attLength(TFile *outFile)
{
    // *****   DECLARING HISTOGRAMS FOR PMT1   *****

    TH1D *att_length_PMT1_ToT = new TH1D("att_length_PMT1_ToT","att_length_PMT1_ToT",279,0.25,139.75);
    att_length_PMT1_ToT->GetXaxis()->SetTitle("position (cm)");
    att_length_PMT1_ToT->GetXaxis()->SetTitleSize(0.06);
    att_length_PMT1_ToT->GetXaxis()->SetTitleOffset(0.7);
    att_length_PMT1_ToT->GetYaxis()->SetTitle("ToT_1_{max} (ns)");
    att_length_PMT1_ToT->GetYaxis()->SetTitleSize(0.06);
    att_length_PMT1_ToT->GetYaxis()->SetTitleOffset(0.7);


    TH1D *att_length_PMT1_ToT_squared = new TH1D("att_length_PMT1_ToT_squared","att_length_PMT1_ToT_squared",279,0.25,139.75);
    att_length_PMT1_ToT_squared->GetXaxis()->SetTitle("position (cm)");
    att_length_PMT1_ToT_squared->GetXaxis()->SetTitleSize(0.06);
    att_length_PMT1_ToT_squared->GetXaxis()->SetTitleOffset(0.7);
    att_length_PMT1_ToT_squared->GetYaxis()->SetTitle("(ToT_1_peak)^{2} (ns^{2})");
    att_length_PMT1_ToT_squared->GetYaxis()->SetTitleSize(0.06);
    att_length_PMT1_ToT_squared->GetYaxis()->SetTitleOffset(0.7);


    TH1D *amplitude_ToT_PMT1_2points = new TH1D("amplitude_ToT_PMT1_2points","amplitude_ToT_PMT1_2points",279,0.25,139.75);
    amplitude_ToT_PMT1_2points->GetXaxis()->SetTitle("position [cm]");
    amplitude_ToT_PMT1_2points->GetXaxis()->SetTitleSize(0.06);
    amplitude_ToT_PMT1_2points->GetXaxis()->SetTitleOffset(0.7);
    amplitude_ToT_PMT1_2points->GetYaxis()->SetTitle("Amplitude [mV]");
    amplitude_ToT_PMT1_2points->GetYaxis()->SetTitleSize(0.06);
    amplitude_ToT_PMT1_2points->GetYaxis()->SetTitleOffset(0.7);


    TH1D *amplitude_ToT_PMT1_3points = new TH1D("amplitude_ToT_PMT1_3points","amplitude_ToT_PMT1_3points",279,0.25,139.75);
    amplitude_ToT_PMT1_3points->GetXaxis()->SetTitle("position [cm]");
    amplitude_ToT_PMT1_3points->GetXaxis()->SetTitleSize(0.06);
    amplitude_ToT_PMT1_3points->GetXaxis()->SetTitleOffset(0.7);
    amplitude_ToT_PMT1_3points->GetYaxis()->SetTitle("Amplitude [mV]");
    amplitude_ToT_PMT1_3points->GetYaxis()->SetTitleSize(0.06);
    amplitude_ToT_PMT1_3points->GetYaxis()->SetTitleOffset(0.7);


    //   *****   DECLARING HISTOGRAMS FOR PMT2   *****

    TH1D *att_length_PMT2_ToT = new TH1D("att_length_PMT2_ToT","att_length_PMT2_ToT",279,0.25,139.75);
    att_length_PMT2_ToT->GetXaxis()->SetTitle("position (cm)");
    att_length_PMT2_ToT->GetXaxis()->SetTitleSize(0.06);
    att_length_PMT2_ToT->GetXaxis()->SetTitleOffset(0.7);
    att_length_PMT2_ToT->GetYaxis()->SetTitle("ToT_2_{max} (ns)");
    att_length_PMT2_ToT->GetYaxis()->SetTitleSize(0.06);
    att_length_PMT2_ToT->GetYaxis()->SetTitleOffset(0.7);


    TH1D *att_length_PMT2_ToT_squared = new TH1D("att_length_PMT2_ToT_squared","att_length_PMT2_ToT_squared",279,0.25,139.75);
    att_length_PMT2_ToT_squared->GetXaxis()->SetTitle("position (cm)");
    att_length_PMT2_ToT_squared->GetXaxis()->SetTitleSize(0.06);
    att_length_PMT2_ToT_squared->GetXaxis()->SetTitleOffset(0.7);
    att_length_PMT2_ToT_squared->GetYaxis()->SetTitle("(ToT_2_peak)^{2} (ns^{2})");
    att_length_PMT2_ToT_squared->GetYaxis()->SetTitleSize(0.06);
    att_length_PMT2_ToT_squared->GetYaxis()->SetTitleOffset(0.7);


    TH1D *amplitude_ToT_PMT2_2points = new TH1D("amplitude_ToT_PMT2_2points","amplitude_ToT_PMT2_2points",279,0.25,139.75);
    amplitude_ToT_PMT2_2points->GetXaxis()->SetTitle("position [cm]");
    amplitude_ToT_PMT2_2points->GetXaxis()->SetTitleSize(0.06);
    amplitude_ToT_PMT2_2points->GetXaxis()->SetTitleOffset(0.7);
    amplitude_ToT_PMT2_2points->GetYaxis()->SetTitle("Amplitude [mV]");
    amplitude_ToT_PMT2_2points->GetYaxis()->SetTitleSize(0.06);
    amplitude_ToT_PMT2_2points->GetYaxis()->SetTitleOffset(0.7);


    TH1D *amplitude_ToT_PMT2_3points = new TH1D("amplitude_ToT_PMT2_3points","amplitude_ToT_PMT2_3points",279,0.25,139.75);
    amplitude_ToT_PMT2_3points->GetXaxis()->SetTitle("position [cm]");
    amplitude_ToT_PMT2_3points->GetXaxis()->SetTitleSize(0.06);
    amplitude_ToT_PMT2_3points->GetXaxis()->SetTitleOffset(0.7);
    amplitude_ToT_PMT2_3points->GetYaxis()->SetTitle("Amplitude [mV]");
    amplitude_ToT_PMT2_3points->GetYaxis()->SetTitleSize(0.06);
    amplitude_ToT_PMT2_3points->GetYaxis()->SetTitleOffset(0.7);


    //   *****   THE END OF THE DECLARING HISTOGRAMS   *****


    for (Int_t j=1; j<279; j++) {  // j<280 before

        att_length_PMT1_ToT->SetBinContent(j,ToT_1_peak[j]);

        att_length_PMT2_ToT->SetBinContent(j,ToT_2_peak[j]);


        att_length_PMT1_ToT_squared->SetBinContent(j,(ToT_1_peak[j])*(ToT_1_peak[j]));

        att_length_PMT2_ToT_squared->SetBinContent(j,(ToT_2_peak[j])*(ToT_2_peak[j]));


        amplitude_ToT_PMT1_2points->SetBinContent(j, a[0] * pow(ToT_1_peak[j], 2) + b[0]);

        amplitude_ToT_PMT2_2points->SetBinContent(j, a[1] * pow(ToT_2_peak[j], 2) + b[1]);


        amplitude_ToT_PMT1_3points->SetBinContent(j, a[2] * pow(ToT_1_peak[j], 2) + b[2]);

        amplitude_ToT_PMT2_3points->SetBinContent(j, a[3] * pow(ToT_2_peak[j], 2) + b[3]);


                                };



    macro macros;

    // pow(TOT, 2)
    TMacro *att_len1;
    qqq << "att_length_PMT1_ToT_squared";
    att_len1 = macros.att_plot(qqq.str().c_str(),0.,140.);
    qqq.str("");

    TMacro *att_len2;
    qqq << "att_length_PMT2_ToT_squared";
    att_len2 = macros.att_plot(qqq.str().c_str(),0.,140.);
    qqq.str("");
    // the end of pow(TOT, 2)


    // just TOT
    TMacro *att_len3;
    qqq << "att_length_PMT1_ToT";
    att_len3 = macros.att_plot(qqq.str().c_str(),0.,140.);
    qqq.str("");

    TMacro *att_len4;
    qqq << "att_length_PMT2_ToT";
    att_len4 = macros.att_plot(qqq.str().c_str(),0.,140.);
    qqq.str("");
    // the end of 'just TOT'


    // A = A(pow(TOT, 2)); further 2 points
    TMacro *amplitude_att_length_1;
    qqq << "amplitude_ToT_PMT1_2points";
    amplitude_att_length_1 = macros.att_plot(qqq.str().c_str(),0.,140.);
    qqq.str("");

    TMacro *amplitude_att_length_2;
    qqq << "amplitude_ToT_PMT2_2points";
    amplitude_att_length_2 = macros.att_plot(qqq.str().c_str(),0.,140.);
    qqq.str("");
    // the end of 'A = A(pow(TOT, 2)); further 2 points'


    // A = A(pow(TOT, 2)); all 3 points
    TMacro *amplitude_tot_pmt_1_3points;
    qqq << "amplitude_ToT_PMT1_3points";
    amplitude_tot_pmt_1_3points = macros.att_plot(qqq.str().c_str(),0.,140.);
    qqq.str("");

    TMacro *amplitude_tot_pmt_2_3points;
    qqq << "amplitude_ToT_PMT2_3points";
    amplitude_tot_pmt_2_3points = macros.att_plot(qqq.str().c_str(),0.,140.);
    qqq.str("");
    // the end of 'A = A(pow(TOT, 2)); all 3 points'

    /// ****
    TMacro *dd;
    qqq << "ddd";
    dd = macros.att_plot(qqq.str().c_str(),0.,140.);
    qqq.str("");



    outFile->mkdir("Attenuation_length");
    outFile->cd("Attenuation_length");

    att_length_PMT1_ToT->Write();
    att_length_PMT2_ToT->Write();

    att_length_PMT1_ToT_squared->Write();
    att_length_PMT2_ToT_squared->Write();

    amplitude_ToT_PMT1_2points->Write();
    amplitude_ToT_PMT2_2points->Write();

    amplitude_ToT_PMT1_3points->Write();
    amplitude_ToT_PMT2_3points->Write();


    att_len1->Write();
    att_len2->Write();
    att_len1->Delete();
    att_len2->Delete();


    att_len3->Write();
    att_len4->Write();
    att_len3->Delete();
    att_len4->Delete();


    amplitude_att_length_1->Write();
    amplitude_att_length_2->Write();
    amplitude_att_length_1->Delete();
    amplitude_att_length_2->Delete();


    amplitude_tot_pmt_1_3points->Write();
    amplitude_tot_pmt_2_3points->Write();
    amplitude_tot_pmt_1_3points->Delete();
    amplitude_tot_pmt_2_3points->Delete();

}
