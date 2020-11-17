#include "TFile.h"
#include "TH2D.h"
#include <TLeaf.h>
#include "TH1D.h"
#include "TH2D.h"
#include "global.h"
#include "MyMainFrame.h"
#include "TLegend.h"
#include "TMacro.h"
//#include "macro.h"

void plotSqrtTotHists(TBranch *eventn, TFile *outFile)
{
    hh[0] = new TH1D("hh1","sqrtTOT_1",300,-7,8);
    hh[1] = new TH1D("hh2","sqrtTOT_2",300,-7,8);
    hh[2] = new TH1D("hh3","sqrtTOTdiff",2400, -12, 12);
    hh[3] = new TH1D("hh4","TOTdiff",2400, -12, 12);

    hh[0]->GetXaxis()->SetTitle("A/#sqrt{ToT_1} + B (ns^{-1/2})");
    hh[0]->GetXaxis()->SetTitleSize(0.06);
    hh[0]->GetXaxis()->SetTitleOffset(0.8);

    hh[1]->GetXaxis()->SetTitle("A/#sqrt{ToT_2} + B (ns^{-1/2})");
    hh[1]->GetXaxis()->SetTitleSize(0.06);
    hh[1]->GetXaxis()->SetTitleOffset(0.8);

    hh[2]->GetXaxis()->SetTitle("A(1/#sqrt{ToT_1} - 1/#sqrt{ToT_2}) + B (ns^{-1/2})");
    hh[2]->GetXaxis()->SetTitleSize(0.06);
    hh[2]->GetXaxis()->SetTitleOffset(0.8);
    hh[2]->SetLineColor(kRed);

    hh[3]->GetXaxis()->SetTitle("A(1/ToT_1 - 1/ToT_2) + B (ns^{-1/2})");
    hh[3]->GetXaxis()->SetTitleSize(0.06);
    hh[3]->GetXaxis()->SetTitleOffset(0.8);
    hh[3]->SetLineColor(kBlack);

    // loop over all events
    for (Int_t i=0; i<eventn->GetEntries(); i++)
    {
        eventn->GetEntry(i);

        ToT_1 = eventn->GetLeaf("adc1")->GetValue();
        ToT_2 = eventn->GetLeaf("adc2")->GetValue();

        //Calculating (tdc1-tdc2)/2 for the given entry
        tdcdiff=(eventn->GetLeaf("tdc1")->GetValue()-eventn->GetLeaf("tdc2")->GetValue())/2;


        // Filling out the first bin

      //  if ((ToT_1<ToT_1_peak[0]+(ToT_1_peak[0]-ToT_1_cut[0]))&&(ToT_2<ToT_2_peak[0]+(ToT_2_peak[0]-ToT_2_cut[0]))) {

        if ((tdcdiff>left_max)&&(tdcdiff<left_max+step/2.)&&(ToT_1>ToT_1_cut[0])&&(ToT_2>ToT_2_cut[0])) {

        hh[0]->Fill(A[0]/sqrt(ToT_1) + B[0]); //Filling out 'hh[0]'

        hh[1]->Fill(A[1]/sqrt(ToT_2) + B[1]); //Filling out 'hh[1]'

        hh[2]->Fill(A[2]*(1/sqrt(ToT_1) - 1/sqrt(ToT_2)) + B[2]); //Filling out 'hh[2]'

        hh[3]->Fill(A[3]*(1/ToT_1 - 1/ToT_2) + B[3]); //Filling out 'hh[3]'

                                                                                                        };
                                                                                                                  //  };


        // Filling out the last bin

    //    if ((ToT_1<ToT_1_peak[278]+(ToT_1_peak[278]-ToT_1_cut[278]))&&(ToT_2<ToT_2_peak[278]+(ToT_2_peak[278]-ToT_2_cut[278]))) {

        if ((tdcdiff>right_max-step/2.)&&(tdcdiff<right_max)&&(ToT_1>ToT_1_cut[278])&&(ToT_2>ToT_2_cut[278])) { // we use bin 278 because
                                                                                                            // bin 279 contains wrong content
        hh[0]->Fill(A[0]/sqrt(ToT_1) + B[0]); //Filling out 'hh[0]'

        hh[1]->Fill(A[1]/sqrt(ToT_2) + B[1]); //Filling out 'hh[1]'

        hh[2]->Fill(A[2]*(1/sqrt(ToT_1) - 1/sqrt(ToT_2)) + B[2]); //Filling out 'hh[2]'

        hh[3]->Fill(A[3]*(1/ToT_1 - 1/ToT_2) + B[3]); //Filling out 'hh[3]'

                                                                                                              };
                                                                                                                        //        };


        // Declaring the number of the bin between the first one and the last one
        Int_t j = int((tdcdiff - left_max+step/2.)/step);

        if ((j>0)&&(j<278)) {

        if ((ToT_1>ToT_1_cut[j])&&(ToT_2>ToT_2_cut[j])) {

    //    if ((ToT_1<ToT_1_peak[j]+(ToT_1_peak[j]-ToT_1_cut[j]))&&(ToT_2<ToT_2_peak[j]+(ToT_2_peak[j]-ToT_2_cut[j]))) {


        hh[0]->Fill(A[0]/sqrt(ToT_1) + B[0]); //Filling out 'hh[0]'

        hh[1]->Fill(A[1]/sqrt(ToT_2) + B[1]); //Filling out 'hh[1]'

        hh[2]->Fill(A[2]*(1/sqrt(ToT_1) - 1/sqrt(ToT_2)) + B[2]); //Filling out 'hh[2]'

        hh[3]->Fill(A[3]*(1/ToT_1 - 1/ToT_2) + B[3]); //Filling out 'hh[3]'


                                                                                                              //      };
                                                        };
                            };


    }; // the end of the loop over all events

    TCanvas *c5 = new TCanvas("c5","comparing",1200,800);

    TH1D *copy_hist = (TH1D*)hh[3]->Clone();
    copy_hist->SetTitle("Combined histograms; A(1/ToT_1 - 1/ToT_2) + B (ns^{-1/2}) vs A(1/#sqrt{ToT_1} - 1/#sqrt{ToT_2}) + B (ns^{-1/2})");

    c5->cd();

    copy_hist->Draw();
    hh[2]->Draw("same");

    TLegend *legend = new TLegend(0.1, 0.8, 0.3, 0.9);
    legend->AddEntry(hh[2],"sqrt","l");
    legend->AddEntry(hh[3],"not sqrt","l");
    legend->Draw();



    MyMainFrame opaa;

    TH1 *hhh = opaa.Smooth_fun(hh[2],180);
    TH1 *qqq = opaa.Smooth_fun(hh[3],180);

    Double_t left_max_hh3, right_max_hh3, left_max_hh4, right_max_hh4;

    left_max_hh3 = opaa.GetTDCleftcut(hhh);
    right_max_hh3 = opaa.GetTDCrightcut(hhh);

    left_max_hh4 = opaa.GetTDCleftcut(qqq);
    right_max_hh4 = opaa.GetTDCrightcut(qqq);

    std::cout << "c_eff_sqrt = " << 140./(right_max_hh3-left_max_hh3)/29.9792 << std::endl;

    std::cout << "c_eff_not_sqrt = " << 140./(right_max_hh4-left_max_hh4)/29.9792 << std::endl;

    TMacro *ttt, *rrr;
    macro macros;

    ttt = macros.TDC_plot("hh3",left_max_hh3,right_max_hh3,hh[2]->GetMaximum());
    rrr = macros.TDC_plot("hh4",left_max_hh4,right_max_hh4,hh[3]->GetMaximum());

    outFile->mkdir("sqrtTOTs");
    outFile->cd("sqrtTOTs");

    hh[0]->Write();
    hh[1]->Write();
    hh[2]->Write();
    hh[3]->Write();
    c5->Write();

    ttt->Write();
    rrr->Write();

    ttt->Delete();
    rrr->Delete();

}
