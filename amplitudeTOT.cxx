#include "TFile.h"
#include <TLeaf.h>
#include <TF1.h>
#include <cmath>
#include <TCanvas.h>
#include <TAxis.h>
#include <TGraph.h>
#include <TFrame.h>
#include <TH1D.h>
#include <TH2D.h>
#include "global.h"

void amplitudeTOT(TFile *outFile)
{
    TCanvas *c7 = new TCanvas("Amplitude_vs_TOT_1","Amplitude_vs_TOT_1",1200,800);
    TCanvas *c8 = new TCanvas("Amplitude_vs_TOT_2","Amplitude_vs_TOT_2",1200,800);


    constexpr Double_t ampl_1[3] = {1265.0, 848.0, 627.86}; // amplitude (mV)
    constexpr Double_t tot_1[3] = {pow(28.43, 2), pow(26.62, 2), pow(23.61, 2)}; // ToT_1 (ns^2)

    constexpr Double_t ampl_2[3] = {592.09, 749.0, 1152.8}; // amplitude (mV)
    constexpr Double_t tot_2[3] = {pow(21.18, 2), pow(23.45, 2), pow(24.15, 2)}; // ToT_1 (ns^2)

    TGraph *gr1 = new TGraph (3, tot_1, ampl_1);
    TGraph *gr11 = new TGraph (3, tot_1, ampl_1);

    gr1->SetMarkerColor(1);
    gr1->SetMarkerStyle(20);
    gr1->SetTitle("A_{1}=A_{1}((ToT_{1})^{2})");
    gr1->GetXaxis()->SetTitle("(ToT_{1})^{2} [ns^{2}]");
    gr1->GetXaxis()->SetTitleOffset(1.4);
    gr1->GetYaxis()->SetTitle("Amplitude, [mV]");

    gr1->Fit("pol1","","",550,720);
    TF1 *lin1 = gr1->GetFunction("pol1");
    b[0] = lin1->GetParameter(0);
    a[0] = lin1->GetParameter(1);

    gr11->Fit("pol1","","",550,820);
    TF1 *lin11 = gr11->GetFunction("pol1");
    lin11->SetLineColor(kBlue);
    b[2] = lin11->GetParameter(0);
    a[2] = lin11->GetParameter(1);


    TGraph *gr2 = new TGraph (3, tot_2, ampl_2);
    TGraph *gr22 = new TGraph (3, tot_2, ampl_2);

    gr2->SetMarkerColor(1);
    gr2->SetMarkerStyle(20);
    gr2->SetTitle("A_{2}=A_{2}((ToT_{2})^{2})");
    gr2->GetXaxis()->SetTitle("(ToT_{2})^{2} [ns^{2}]");
    gr2->GetXaxis()->SetTitleOffset(1.4);
    gr2->GetYaxis()->SetTitle("Amplitude, [mV]");
    gr2->Draw("AP");

    gr2->Fit("pol1","","",445,555);
    TF1 *lin2 = gr2->GetFunction("pol1");
    b[1] = lin2->GetParameter(0);
    a[1] = lin2->GetParameter(1);

    gr22->Fit("pol1","","",445,590);
    TF1 *lin22 = gr22->GetFunction("pol1");
    lin22->SetLineColor(kBlue);
    b[3] = lin22->GetParameter(0);
    a[3] = lin22->GetParameter(1);



    outFile->mkdir("Amplitude_vs_ToT");
    outFile->cd("Amplitude_vs_ToT");

    c7->cd();
    gr1->Draw("AP");
    gr11->Draw("P");

    c8->cd();
    gr2->Draw("AP");
    gr22->Draw("P");


    c7->Write();
    c8->Write();
}
