#include <TGFrame.h>
#include <RQ_OBJECT.h>

#include <TGNumberEntry.h>
#include <sstream>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <stdio.h>
#include <TGLabel.h>
#include <TGProgressBar.h>
#include <TGComboBox.h>
#include <TH1.h>
#include <TTree.h>
#include <TMacro.h>
#include <TMinuit.h>
#include "macro.h"
#include <RooLandau.h>
#include <RooNumConvPdf.h>
#include <RooDataHist.h>
#include <RooBinning.h>
#include <RooAbsPdf.h>
#include <RooRealVar.h>
#include <RooArgSet.h>
#include <RooCmdArg.h>
#include <RooGaussian.h>
#include <RooMsgService.h>
#include "RooDataSet.h"
#include "RooRealVar.h"
#include "RooGaussian.h"
#include "RooGlobalFunc.h"
#include "RooFitResult.h"
#include "RooProdPdf.h"
#include "RooCmdArg.h"
#include "RooMsgService.h"
//#include "MakeCuts.h"



using namespace std;
using namespace RooFit;


class MyMainFrame
{
        RQ_OBJECT("MyMainFrame")
private:
        macro macros;
        TGComboBox *fCombo;
        TGComboBox *fNumPoints;
	TGCheckButton *estat;
	TGCheckButton *inc_langau;
        TGHProgressBar *fHProg1;
	TGLabel *label_ref_pmt;
	TGNumberEntry *ref_pmt;
        TGTextButton *go;
	TGTextButton *input_file;
	TGTextButton *output_file;
        TGMainFrame *fMain;
	TGTextButton *exit;
	TGHorizontalFrame *hframe;

//	TGNumberEntry *n_points;
        TGLabel *label_n_points;
	TString path;
	Double_t bar_length[62];
	const char* npoints_char[27];
	short nfiles;
	std::string _current_file;
	std::string _out_file;
	std::string _out_dir;
	TGLabel *labelq;
	TGLabel *labelqout;
	TGLabel *labellength;
	Bool_t file_status;
	TTree *t21;

public:
	Double_t GetADCoffsetcut(TH1 *h);
	Double_t GetTDCrightcut(TH1 *h)  // Definition of GetTDCrightcut finction
	{
        Int_t i, j, a,ib;
        a = h->GetNbinsX();

        Double_t b, bmax, ymax;
        ymax = h->GetMaximumBin();
        ymax = h->GetBinContent(ymax);

        TH1D *hmin = new TH1D("min","min",a-h->GetMaximumBin(),h->GetBinLowEdge(h->GetMaximumBin()),h->GetBinLowEdge(a));

        for (i=h->GetMaximumBin(); i<=a; i++)
        {

        hmin->Fill(h->GetBinCenter(i),Double_t(fabs(h->GetBinContent(i)-ymax/2.)));

        }

        b=hmin->GetBinCenter(hmin->GetMinimumBin());

        hmin->Delete();

        return b;

        };


	Double_t GetTDCleftcut(TH1 *h)  // Definition of GetTDCleftcut finction
	{
        Int_t i, j, a, ib;
        a = h->GetNbinsX();

        Double_t b, bmax, ymax;
        ymax = h->GetMaximumBin();
        ymax = h->GetBinContent(ymax);

        TH1D *hmin = new TH1D("min","min",h->GetMaximumBin(),h->GetBinLowEdge(0),h->GetBinLowEdge(h->GetMaximumBin()));

        for (i=0; i<=h->GetMaximumBin(); i++)
        {

        hmin->Fill(h->GetBinCenter(i), Double_t(fabs(h->GetBinContent(i)-ymax/2.)));

        }

        b=hmin->GetBinCenter(hmin->GetMinimumBin());

        hmin->Delete();

        return b;

        };


	TH1*  Smooth_fun(TH1 *h, Int_t bin_num)  // Definition of Smooth_fun finction
	{
        Int_t i,j,a;
        a = h->GetNbinsX();

        ostringstream hist_name;
        ostringstream hist_title;

        hist_name << h->GetName() << "_smooth";
        hist_title << h->GetTitle() << "_smooth";

        TH1* h1 = new    TH1D(hist_name.str().c_str(),hist_title.str().c_str(),a,h->GetBinLowEdge(1),h->GetBinLowEdge(a)+h->GetBinWidth(a));

        hist_name.str("");
        hist_title.str("");

        Double_t y, width;
        width=h->GetBinWidth(a);

        for (i=1; i<=a-bin_num; i++)
        {
        y=0;
        for (j=0; j<=bin_num-1; j++)
        {
        y=y+h->GetBinContent(i+j)/bin_num;
        };
        h1->SetBinContent(i+bin_num/2,y);
        };
        return h1;
        };

	Double_t landauconvgauss(TH1I *h, Double_t &err);
	Double_t myFunction(TH1 *h);
	string inpfile_inp;
	string outfile_inp;

        void MainFrame(string inpfile_in, string outfile_in);


    //    void MainFrame();
        void MakeAnalysis();

};
