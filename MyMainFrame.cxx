#include <TBranch.h>
#include "TFile.h"
#include "MyMainFrame.h"
#include "plotTdcDiff.h"
#include "plotTOTs.h"
#include "findPeaksCutsOffsets.h"
#include "makeCuts.h"
#include "attLength.h"
#include "amplitudeTOT.h"
#include "plotCorr.h"
#include "fitCorr.h"
#include "plotSqrtTotHists.h"
#include "compareTdcDiff.h"

void MyMainFrame::MainFrame(std::string inpfile_in, std::string outfile_in)
{

    inpfile_inp = inpfile_in;
		outfile_inp = outfile_in;

    MakeAnalysis();

}


void MyMainFrame::MakeAnalysis()
{

		TFile *finp;

    finp = new TFile(inpfile_inp.c_str());

    TTree *t20 = (TTree*)finp->Get("t20");

    TBranch *eventn;

    eventn = t20->GetBranch("eventn");

    TFile *outFile;

    outFile = new TFile(outfile_inp.c_str(),"RECREATE");


    plotTdcDiff(eventn, outFile); // plots tdcdiff and its smooth case, paints boundaries

    plotTOTs(eventn, outFile); // plots ToT_1_(j) and ToT_2_(j) (smooth cases too), where j is from 0 to 279

    findPeaksCutsOffsets(outFile); // finds and draws ToT's peaks, cuts, and offsets for ToT_1_(j) and ToT_2_(j)

    makeCuts(eventn, outFile); // plots tdcdiff and its smooth case, paints boundaries after applying cuts

    amplitudeTOT(outFile);

    attLength(outFile); // plots att length histograms

    plotCorr(eventn, outFile);  // plots corr histograms (2-D hists)

    fitCorr(outFile); // fits corr-hists with a linear functions

    plotSqrtTotHists(eventn, outFile); // plots tdcdiff another way (sqrt(ToT))

    compareTdcDiff(outFile); // plots tdcdiff distribution drawn 2 diffrent ways on the same canvas

}
