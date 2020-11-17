#include "TH2D.h"
#include "TFile.h"
#include <TLeaf.h>
#include "global.h"

void plotCorr(TBranch *eventn, TFile *outFile)
{
    corr[0] = new TH2D("corr1","corr_1",100,0.16,0.3,100,left_max,right_max);
    corr[1] = new TH2D("corr2","corr_2",100,0.16,0.3,100,left_max,right_max);
    corr[2] = new TH2D("corr3","corr_3",100,-0.15,0.15,100,left_max,right_max);
    corr[3] = new TH2D("corr4","corr_4",100,-0.05,0.05,100,left_max,right_max);

    corr[0]->GetXaxis()->SetTitle("1/#sqrt{ToT_1} (ns^{-1/2})");
    corr[0]->GetXaxis()->SetTitleSize(0.06);
    corr[0]->GetXaxis()->SetTitleOffset(0.8);
    corr[0]->GetYaxis()->SetTitle("tdcdiff (ns)");
    corr[0]->GetYaxis()->SetTitleSize(0.06);
    corr[0]->GetYaxis()->SetTitleOffset(0.7);
    corr[0]->SetOption("colz");

    corr[1]->GetXaxis()->SetTitle("1/#sqrt{ToT_2} (ns^{-1/2})");
    corr[1]->GetXaxis()->SetTitleSize(0.06);
    corr[1]->GetXaxis()->SetTitleOffset(0.8);
    corr[1]->GetYaxis()->SetTitle("tdcdiff (ns)");
    corr[1]->GetYaxis()->SetTitleSize(0.06);
    corr[1]->GetYaxis()->SetTitleOffset(0.7);
    corr[1]->SetOption("colz");

    corr[2]->GetXaxis()->SetTitle("1/#sqrt{ToT_1} - 1/#sqrt{ToT_2} (ns^{-1/2})");
    corr[2]->GetXaxis()->SetTitleSize(0.06);
    corr[2]->GetXaxis()->SetTitleOffset(0.8);
    corr[2]->GetYaxis()->SetTitle("tdcdiff (ns)");
    corr[2]->GetYaxis()->SetTitleSize(0.06);
    corr[2]->GetYaxis()->SetTitleOffset(0.7);
    corr[2]->SetOption("colz");

    corr[3]->GetXaxis()->SetTitle("1/ToT_1 - 1/ToT_2 (ns^{-1/2})");
    corr[3]->GetXaxis()->SetTitleSize(0.06);
    corr[3]->GetXaxis()->SetTitleOffset(0.8);
    corr[3]->GetYaxis()->SetTitle("tdcdiff (ns)");
    corr[3]->GetYaxis()->SetTitleSize(0.06);
    corr[3]->GetYaxis()->SetTitleOffset(0.7);
    corr[3]->SetOption("colz");

    // loop over all events
    for (Int_t i=0; i<eventn->GetEntries(); i++)
    {

        eventn->GetEntry(i);

        ToT_1 = eventn->GetLeaf("adc1")->GetValue();
        ToT_2 = eventn->GetLeaf("adc2")->GetValue();

        //Calculating (tdc1-tdc2)/2 for the given entry
        tdcdiff=(eventn->GetLeaf("tdc1")->GetValue()-eventn->GetLeaf("tdc2")->GetValue())/2;


        // Filling out the first bin

        if ((ToT_1<ToT_1_peak[0]+(ToT_1_peak[0]-ToT_1_cut[0]))&&(ToT_2<ToT_2_peak[0]+(ToT_2_peak[0]-ToT_2_cut[0]))) {

        if ((tdcdiff>left_max)&&(tdcdiff<left_max+step/2.)&&(ToT_1>ToT_1_cut[0])&&(ToT_2>ToT_2_cut[0])) {

        corr[0]->Fill(1./sqrt(ToT_1),tdcdiff); //Filling out 'corr[0]'

        corr[1]->Fill(1./sqrt(ToT_2),tdcdiff); //Filling out 'corr[1]'

        corr[2]->Fill(1./sqrt(ToT_1) - 1./sqrt(ToT_2),tdcdiff); //Filling out 'corr[2]'

        corr[3]->Fill(1./ToT_1 - 1./ToT_2,tdcdiff);

                                                                                                         };
                                                                                                                     };


        // Filling out the last bin

        if ((ToT_1<ToT_1_peak[278]+(ToT_1_peak[278]-ToT_1_cut[278]))&&(ToT_2<ToT_2_peak[278]+(ToT_2_peak[278]-ToT_2_cut[278]))) {

        if ((tdcdiff>right_max-step/2.)&&(tdcdiff<right_max)&&(ToT_1>ToT_1_cut[278])&&(ToT_2>ToT_2_cut[278]))  {  // we use bin 278 because
                                                                                                            // bin 279 contains wrong content
        corr[0]->Fill(1./sqrt(ToT_1),tdcdiff); //Filling out 'corr[0]'

        corr[1]->Fill(1./sqrt(ToT_2),tdcdiff); //Filling out 'corr[1]'

        corr[2]->Fill(1./sqrt(ToT_1) - 1./sqrt(ToT_2),tdcdiff); //Filling out 'corr[2]

        corr[3]->Fill(1./ToT_1 - 1./ToT_2,tdcdiff);

                                                                                                               };
                                                                                                                                 };


        // Declaring the number of the bin between the first one and the last one
        Int_t j = int((tdcdiff - left_max+step/2.)/step);

        if ((j>0)&&(j<278)) {

        if ((ToT_1>ToT_1_cut[j])&&(ToT_2>ToT_2_cut[j])) {
                                                           // the peaks are supposed to be distributed by gauss
        if ((ToT_1<ToT_1_peak[j]+(ToT_1_peak[j]-ToT_1_cut[j]))&&(ToT_2<ToT_2_peak[j]+(ToT_2_peak[j]-ToT_2_cut[j]))) {

        corr[0]->Fill(1./sqrt(ToT_1),tdcdiff);

        corr[1]->Fill(1./sqrt(ToT_2),tdcdiff);

        corr[2]->Fill(1./sqrt(ToT_1) - 1./sqrt(ToT_2),tdcdiff);

        corr[3]->Fill(1./ToT_1 - 1./ToT_2,tdcdiff);

                                                                                                                    };
                                                        };
                            };


    }; // the end of the loop over all events


    outFile->cd();

    outFile->mkdir("Correction");
    outFile->cd("Correction");

    corr[0]->Write();
    corr[1]->Write();
    corr[2]->Write();
    corr[3]->Write();

}
