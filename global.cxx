#include "TH1D.h"
#include "TH1.h"
#include <sstream>
#include "TH2D.h"
#include <TBranch.h>

    // plotTdcDiff()
    TH1D *hist_tdcdiff;

    TH1 *hist_tdcdiff_smooth;

    Double_t left_max;

    Double_t right_max;


    // plotTOTs
    TH1D *hist_ToT_1[280];

    TH1D *hist_ToT_2[280];

    TH1D *hist_ToT_3[280];

    TH1 *hist_ToT_1_smooth[280];

    TH1 *hist_ToT_2_smooth[280];

    TH1 *hist_ToT_3_smooth[280];

    Double_t step;

    std::ostringstream qqq;

    Double_t tdcdiff,ToT_1,ToT_2;


    // findPeaksCutsOffsets
    Double_t ToT_1_offset[280];

    Double_t ToT_2_offset[280];

    Double_t ToT_1_peak[280];

    Double_t ToT_2_peak[280];

    Double_t ToT_1_cut[280];

    Double_t ToT_2_cut[280];


    // makeCuts
    TH1D *hist_tdcdiff_with_cuts;


    // amplitudeTOT
    Double_t a[3], b[3];


    // attLength
    // nothing


    // plotCorr
    TH2D *corr[4];


    // fitCorr
    Double_t A[4], B[4];


    // plotSqrtTotHists
    TH1D *hh[3];
