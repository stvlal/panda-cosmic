#ifndef GLOBAL_H
#define GLOBAL_H

    // plotTdcDiff()
    extern TH1D *hist_tdcdiff;

    extern TH1 *hist_tdcdiff_smooth;

    extern Double_t left_max;

    extern Double_t right_max;


    // plotTOTs()
    extern TH1D *hist_ToT_1[280];

    extern TH1D *hist_ToT_2[280];

    extern TH1D *hist_ToT_3[280];

    extern TH1 *hist_ToT_1_smooth[280];

    extern TH1 *hist_ToT_2_smooth[280];

    extern TH1 *hist_ToT_3_smooth[280];

    extern Double_t step;

    extern std::ostringstream qqq;

    extern Double_t tdcdiff,ToT_1,ToT_2;


    // findPeaksCutsOffsets
    extern Double_t ToT_1_offset[280];

    extern Double_t ToT_2_offset[280];

    extern Double_t ToT_1_peak[280];

    extern Double_t ToT_2_peak[280];

    extern Double_t ToT_1_cut[280];

    extern Double_t ToT_2_cut[280];


    // makeCuts
    extern TH1D *hist_tdcdiff_with_cuts;


    // amplitudeTOT
    extern Double_t a[3], b[3];


    // attLength
    // nothing


    // plotCorr
    extern TH2D *corr[4];


    // fitCorr
    extern Double_t A[4], B[4];


    // plotSqrtTotHists
    extern TH1D *hh[3];


#endif
