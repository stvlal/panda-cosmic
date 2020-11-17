#include "TH1D.h"
#include "TH1.h"
#include "TH2D.h"
#include <TBranch.h>
#include "TFile.h"
#include <TLeaf.h>
#include "MyMainFrame.h"
#include "global.h"

void plotTOTs(TBranch *eventn, TFile *outFile)
{
    //Calculating the step size over (tdc2-tdc1)/2
    step = (right_max-left_max)/280.;

    //Setting 'qqq' to nothing (there is std::ostringstream qqq in global.cxx)
    qqq.str("");

    //Loop over ToT histogram number
    for (Int_t j=0; j<280; j++)
    {
        //Setting name of the ToT_1 histogram
        qqq << "ToT_1_" << j;

        //Declaring ToT_1 histogram number 'j'
        hist_ToT_1[j] = new TH1D(qqq.str().c_str(),qqq.str().c_str(),1000,0.,100.);

        //Setting 'qqq' to nothing
        qqq.str("");

        hist_ToT_1[j]->GetXaxis()->SetTitle("ToT (ns)");
        hist_ToT_1[j]->GetXaxis()->SetTitleSize(0.06);
        hist_ToT_1[j]->GetXaxis()->SetTitleOffset(0.7);


        //Setting name of the ToT_2 histogram
        qqq << "ToT_2_" << j;

        //Declaring ToT_2 histogram number 'j'
        hist_ToT_2[j] = new TH1D(qqq.str().c_str(),qqq.str().c_str(),1000,0.,100.);

        //Setting 'qqq' to nothing
        qqq.str("");

        hist_ToT_2[j]->GetXaxis()->SetTitle("ToT (ns)");
        hist_ToT_2[j]->GetXaxis()->SetTitleSize(0.06);
        hist_ToT_2[j]->GetXaxis()->SetTitleOffset(0.7);


        //Setting name of the ToT_2 histogram
        qqq << "ToT_3_" << j;

        //Declaring ToT_2 histogram number 'j'
        hist_ToT_3[j] = new TH1D(qqq.str().c_str(),qqq.str().c_str(),1000,0.,100.);

        //Setting 'qqq' to nothing
        qqq.str("");

        hist_ToT_3[j]->GetXaxis()->SetTitle("ToT (ns)");
        hist_ToT_3[j]->GetXaxis()->SetTitleSize(0.06);
        hist_ToT_3[j]->GetXaxis()->SetTitleOffset(0.7);

    }; // the end of the loop over ToT histogram number


    //Loop over all events in 't20'
    for (Int_t i=0; i<eventn->GetEntries(); i++)
    {
        eventn->GetEntry(i);  //Getting the entery number 'i'

        if (eventn->GetLeaf("adc1")->GetValue()<100.) {  //Checking that ToT_1 < 100

        //Calculating (tdc1-tdc2)/2 for the given entry
        tdcdiff=(eventn->GetLeaf("tdc1")->GetValue()-eventn->GetLeaf("tdc2")->GetValue())/2;


        if ((tdcdiff>left_max)&&(tdcdiff<left_max+step/2.)){ //Checking if the event within bin zero

        hist_ToT_1[0]->Fill(eventn->GetLeaf("adc1")->GetValue()); //Filling out ToT_1 for bin zero

                                                           };


        if ((tdcdiff>right_max-step/2.)&&(tdcdiff<right_max)){ //Checking if the event within the last bin

        hist_ToT_1[279]->Fill(eventn->GetLeaf("adc1")->GetValue()); //Filling out ToT_1 for the last bin

                                                             };


        Int_t j = int((tdcdiff - left_max+step/2.)/step);

        if ((j>0)&&(j<279)) {

        hist_ToT_1[j]->Fill(eventn->GetLeaf("adc1")->GetValue()); //Filling out ToT_1 for the bin 'j'

                            };

                                                      }; //End of ToT_1<100 if



        if (eventn->GetLeaf("adc2")->GetValue()<100.) {   //Checking that ToT_2 < 100

        //Calculating (tdc1-tdc2)/2 for the given entry
        tdcdiff=(eventn->GetLeaf("tdc1")->GetValue()-eventn->GetLeaf("tdc2")->GetValue())/2;


        if ((tdcdiff>left_max)&&(tdcdiff<left_max+step/2.)){ //Checking if the event within bin zero

        hist_ToT_2[0]->Fill(eventn->GetLeaf("adc2")->GetValue()); //Filling out ToT_2 for bin zero

                                                           };


        if ((tdcdiff>right_max-step/2.)&&(tdcdiff<right_max)){ //Checking if the event within the last bin

        hist_ToT_2[279]->Fill(eventn->GetLeaf("adc2")->GetValue()); //Filling out ToT_2 for the last bin

                                                              };


        Int_t j = int((tdcdiff - left_max+step/2.)/step);

        if ((j>0)&&(j<279)) {

        hist_ToT_2[j]->Fill(eventn->GetLeaf("adc2")->GetValue()); //Filling out ToT_2 for the bin 'j'

                            };

                                                      }; //End of ToT_2<100 if



        if (eventn->GetLeaf("adc0")->GetValue()<100.) {   //Checking that ToT_3 < 100

        //Calculating (tdc1-tdc2)/2 for the given entry
        tdcdiff=(eventn->GetLeaf("tdc1")->GetValue()-eventn->GetLeaf("tdc2")->GetValue())/2;


        if ((tdcdiff>left_max)&&(tdcdiff<left_max+step/2.)){ //Checking if the event within bin zero

        hist_ToT_3[0]->Fill(eventn->GetLeaf("adc0")->GetValue()); //Filling out ToT_3 for bin zero

                                                           };


        if ((tdcdiff>right_max-step/2.)&&(tdcdiff<right_max)){ //Checking if the event within the last bin

        hist_ToT_3[279]->Fill(eventn->GetLeaf("adc0")->GetValue()); //Filling out ToT_3 for the last bin

                                                              };


        Int_t j = int((tdcdiff - left_max+step/2.)/step);

        if ((j>0)&&(j<279)) {

        hist_ToT_3[j]->Fill(eventn->GetLeaf("adc0")->GetValue()); //Filling out ToT_3 for the bin 'j'

                            };

                                                      }; //End of ToT_3<100 if

    }; // The end of the loop over all events in 't20'


    MyMainFrame oppa;

    //Loop over the bins
    for (Int_t j=0; j<280; j++)
    {
        //Smoothing ToT_1 hist
        hist_ToT_1_smooth[j] = oppa.Smooth_fun(hist_ToT_1[j],40);

        //String for smoothing ToT_1 name
        qqq << "ToT_1_" << j << "_smooth";

        //Setting new name and title for 'hist_ToT_1_smooth[j]'
        hist_ToT_1_smooth[j]->SetName(qqq.str().c_str());
        hist_ToT_1_smooth[j]->SetTitle(qqq.str().c_str());

        //Setting qqq to nothing
        qqq.str("");


        //Smoothing ToT_2 hist
        hist_ToT_2_smooth[j] = oppa.Smooth_fun(hist_ToT_2[j],40);

        //String for smoothing ToT_2 name
        qqq << "ToT_2_" << j << "_smooth";

        //Setting new name and title for 'hist_ToT_2_smooth[j]'
        hist_ToT_2_smooth[j]->SetName(qqq.str().c_str());
        hist_ToT_2_smooth[j]->SetTitle(qqq.str().c_str());

        //Setting qqq to nothing
        qqq.str("");


        //Smoothing ToT_3 hist
        hist_ToT_3_smooth[j] = oppa.Smooth_fun(hist_ToT_3[j],40);

        //String for smoothing ToT_3 name
        qqq << "ToT_3_" << j << "_smooth";

        //Setting new name and title for 'hist_ToT_3_smooth[j]'
        hist_ToT_3_smooth[j]->SetName(qqq.str().c_str());
        hist_ToT_3_smooth[j]->SetTitle(qqq.str().c_str());

        //Setting qqq to nothing
        qqq.str("");

    };


    outFile->mkdir("ToT_1");
    outFile->cd("ToT_1");

    for (Int_t j=0; j<280; j++)
    {
        hist_ToT_1[j]->SetEntries(hist_ToT_1[j]->Integral(1,1000));
        hist_ToT_1[j]->Write();

        hist_ToT_1_smooth[j]->GetXaxis()->SetTitle("ToT (ns)");
        hist_ToT_1_smooth[j]->GetXaxis()->SetTitleSize(0.06);
        hist_ToT_1_smooth[j]->GetXaxis()->SetTitleOffset(0.7);

        hist_ToT_1_smooth[j]->SetEntries(hist_ToT_1[j]->Integral(1,1000));
        hist_ToT_1_smooth[j]->Write();
    };

    outFile->mkdir("ToT_2");
    outFile->cd("ToT_2");

    for (Int_t j=0; j<280; j++)
    {
        hist_ToT_2[j]->SetEntries(hist_ToT_2[j]->Integral(1,1000));
        hist_ToT_2[j]->Write();

        hist_ToT_2_smooth[j]->GetXaxis()->SetTitle("ToT (ns)");
        hist_ToT_2_smooth[j]->GetXaxis()->SetTitleSize(0.06);
        hist_ToT_2_smooth[j]->GetXaxis()->SetTitleOffset(0.7);

        hist_ToT_2_smooth[j]->SetEntries(hist_ToT_2[j]->Integral(1,1000));
        hist_ToT_2_smooth[j]->Write();
     };

    outFile->mkdir("ToT_3");
    outFile->cd("ToT_3");

    for (Int_t j=0; j<280; j++)
    {
        hist_ToT_3[j]->SetEntries(hist_ToT_3[j]->Integral(1,1000));
        hist_ToT_3[j]->Write();

        hist_ToT_3_smooth[j]->GetXaxis()->SetTitle("ToT (ns)");
        hist_ToT_3_smooth[j]->GetXaxis()->SetTitleSize(0.06);
        hist_ToT_3_smooth[j]->GetXaxis()->SetTitleOffset(0.7);

        hist_ToT_3_smooth[j]->SetEntries(hist_ToT_3[j]->Integral(1,1000));
        hist_ToT_3_smooth[j]->Write();
    };
}
