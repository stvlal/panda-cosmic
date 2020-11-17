#include "TProfile.h"
#include "TF1.h"
#include <iostream>
#include "TFile.h"
#include <TLeaf.h>
#include "TH2D.h"
#include "global.h"
#include <TCanvas.h>

void fitCorr(TFile *outFile)
{
    TProfile *prof1 = corr[0]->ProfileX();  // making profile my 2-d hist (look pdf-doc about what ProfileX means)
    prof1->Fit("pol1","","",0.2,0.235);
    TF1 *f111 = prof1->GetFunction("pol1"); // getting a linear function
    B[0] = f111->GetParameter(0);  // getting parameter B
    A[0] = f111->GetParameter(1);  // getting parameter A
    f111->SetName("f111");

    TProfile *prof2 = corr[1]->ProfileX();  // making profile my 2-d hist (look pdf-doc about what ProfileX means)
    prof2->Fit("pol1","","",0.22,0.245);
    TF1 *f222 = prof2->GetFunction("pol1"); // getting a linear function
    B[1] = f222->GetParameter(0);  // getting parameter B
    A[1] = f222->GetParameter(1);  // getting parameter A
    f222->SetName("f222");

    TProfile *prof3 = corr[2]->ProfileX();  // making profile my 2-d hist (look pdf-doc about what ProfileX means)
    prof3->Fit("pol1","","",-0.03,0.01);
    TF1 *f333 = prof3->GetFunction("pol1"); // getting a linear function
    B[2] = f333->GetParameter(0);  // getting parameter B
    A[2] = f333->GetParameter(1);  // getting parameter A
    f333->SetName("f333");

    TProfile *prof4 = corr[3]->ProfileX();  // making profile my 2-d hist (look pdf-doc about what ProfileX means)
    prof4->Fit("pol1","","",-0.012,0.004);
    TF1 *f444 = prof4->GetFunction("pol1"); // getting a linear function
    B[3] = f444->GetParameter(0);  // getting parameter B
    A[3] = f444->GetParameter(1);  // getting parameter A
    f444->SetName("f444");

    // Declaring canvases for drawing histograms and linear functions

    TCanvas *c1 = new TCanvas("c1","Corr_1",1200,800);
    c1->Divide(2,1);

    TCanvas *c2 = new TCanvas("c2","Corr_2",1200,800);
    c2->Divide(2,1);

    TCanvas *c3 = new TCanvas("c3","Corr_3",1200,800);
    c3->Divide(2,1);

    TCanvas *c6 = new TCanvas("c6","Corr_4",1200,800);
    c6->Divide(2,1);


    c1->cd(1);
    corr[0]->Draw();
    c1->cd(2);
    prof1->Draw();

    c2->cd(1);
    corr[1]->Draw();
    c2->cd(2);
    prof2->Draw();

    c3->cd(1);
    corr[2]->Draw();
    c3->cd(2);
    prof3->Draw();

    c6->cd(1);
    corr[3]->Draw();
    c6->cd(2);
    prof4->Draw();


    outFile->mkdir("corr_profile");
    outFile->cd("corr_profile");

    c1->Write();
    c2->Write();
    c3->Write();
    c6->Write();

}
