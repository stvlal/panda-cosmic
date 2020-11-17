#include <iostream>
#include <string>
#include <vector>
#include "MyMainFrame.h"

using namespace std;


int main(int argc, char** argv) {


    vector<string> args;


    Int_t i;
    string inpfile_inp = "";
    string outfile_inp = "";


    for (i=1;i<argc;i++)
        args.push_back(argv[i]);


   int optind=1;
     while ((optind < argc) && (argv[optind][0]=='-')) {
        string sw = argv[optind];
	string sw1 = argv[optind];
	string sw2 = argv[optind];
	string sw3 = argv[optind];
	string sw5 = argv[optind];


       if (sw=="-i") {
            optind++;
	    if (!(optind < argc))
	    {
	    cout << "WRONG FILE NAME" << "\n";
	    return 0;
	    };
	    inpfile_inp = argv[optind];
            cout << "input file is " << inpfile_inp << "\n";
	}




	else if (sw2.replace(sw2.begin()+2,sw2.end(),"")=="-i") {
	    sw2 = argv[optind];
	    sw2.replace(sw2.begin(),sw2.begin()+2,"");
	    inpfile_inp = sw2;
            cout << "input file is " << inpfile_inp << "\n";
        }



	else if (sw=="-o") {
            optind++;
	    if (!(optind < argc))
	    {
	    cout << "WRONG FILE NAME" << "\n";
	    return 0;
	    };
	    sw5 = argv[optind];
	    if (sw5.replace(sw5.begin(),sw5.end()-5,"") != ".root") {
	     cout << "OUTPUT FILE NEED TO BE *.root" << "\n";
	    return 0;
	    };
	    outfile_inp = argv[optind];
            cout << "output file is " << outfile_inp << "\n";
	 }




	else if (sw3.replace(sw3.begin()+2,sw3.end(),"")=="-o") {
	    if (sw5.replace(sw5.begin(),sw5.end()-5,"") != ".root") {
	    cout << "OUTPUT FILE NEED TO BE *.root" << "\n";
	    return 0;
	    };
	    sw3 = argv[optind];
	    sw3.replace(sw3.begin(),sw3.begin()+2,"");
	    outfile_inp = sw3;
            cout << "output file is " << outfile_inp << "\n";
        }



        else {
            cout << "Unknown switch: "
                 << argv[optind] << endl;
		 return 0;
		 }
        optind++;
    }



    if (inpfile_inp == "") {
    cout << "NO INPUT FILE" << "\n";
	    return 0;
    };

    if (outfile_inp == "") {
    cout << "NO OUTPUT FILE" << "\n";
	    return 0;
    };


    MyMainFrame jopa;
    jopa.MainFrame(inpfile_inp,outfile_inp);


    return 0;
}
