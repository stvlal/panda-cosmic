#include <TCanvas.h>
#include "TH1D.h"
#include "TH2D.h"
#include "TLegend.h"
#include <TBranch.h>
#include "TFile.h"
#include "global.h"

void compareTdcDiff(TFile *outFile)
{
    TCanvas *c4 = new TCanvas("c4","two histograms",1200,800);

    TH1D *copy = (TH1D*)hh[2]->Clone();
    copy->SetTitle("Combined histograms;(tdc1-tdc2)/2 (ns) vs A(1/#sqrt{ToT_1} - 1/#sqrt{ToT_2}) + B (ns^{-1/2})");

    c4->cd();

    copy->Draw();
    hist_tdcdiff_with_cuts->Draw("same");

    TLegend *legend = new TLegend(0.1, 0.7, 0.4, 0.9);
    legend->AddEntry(hh[2],"Histogram filled with using corr-hists","l");
    legend->AddEntry(hist_tdcdiff_with_cuts,"Histogram filled with using usual cuts ","l");
    legend->Draw();


    outFile->mkdir("combined_hists");
    outFile->cd("combined_hists");

    c4->Write();

    outFile->Close();

}
