TCanvas* MakePlot(TTree * tree, TString var = "mass", TString varName = "M", TString cut = "abs(pdgID == 6)"){
    // Draw by
    // LHETree->Draw("pt","abs(pdgID) == 6")
    TString cname = var;
    cname += " with ";
    cname += cut;

//    TH1F *hvar;// = new TH1F("h1","h1",50,1);
    TString varh = var;
    varh += ";";
    varh += varName;
    varh += ";; >>";
    varh += varName;

//    cout << "varh " << varh << endl;
//    cout << hvar->GetName() << endl;

    TCanvas * cvar = new TCanvas(varName,cname,600,600);
    tree->Draw(varh, cut);
    cvar->SetLogy();

//    hvar->GetXaxis()->SetTitle(varName);
//    cvar->GetXaxis()->SetTitleSize(0.5);
//    cout << var << "\t" << varName << "\t" << cut << endl;

    return cvar;
}

//void MakeValidationPlots(TString fname="T1tttt_gluino_800_LSP_450_all.root", TString foutname = "plots.root"){
void MakeValidationPlots(TString fname="T2qq_2j_squark_950.root", TString prefix = "t2qq_"){
    gStyle->SetPadBottomMargin(0.15);

    TFile * fp = new TFile(fname,"READ");
    TTree * tree = (TTree*) fp->Get("LHETree");

    const int Nplot = 16;

    TString vars[Nplot] = {"mass","mass","mass","mass","phi","eta","eta","phi","eta","pt","eta","phi","pt","mass","mass","pdgID"};
    TString varNames[Nplot] = {"M_t","M_W","M_go","M_lsp","Phi_all","Eta_all","Eta_all_cut","Phi_t","Eta_t","Pt_lep","Eta_lep","Phi_lep","Pt_t","M_chi","Msq","PdgID"};
    TString cuts[Nplot] = {"abs(pdgID) == 6","abs(pdgID) == 24","abs(pdgID) == 1000021","abs(pdgID) == 1000022","state > 0","state > 0","abs(eta) < 5 ","abs(pdgID) == 6","abs(pdgID) == 6","abs(pdgID) > 9 && abs(pdgID) < 20","abs(pdgID) > 9 && abs(pdgID) < 20","abs(pdgID) > 9 && abs(pdgID) < 20","abs(pdgID) == 6","abs(pdgID) == 1000024","(abs(pdgID) > 1000000 && abs(pdgID) < 1000010) || (abs(pdgID) > 2000000 && abs(pdgID) < 2000010)","(abs(pdgID) < 25) && (state > 0)"};

    TString foutname = prefix + "plots.root";
    TFile *fout = new TFile(foutname, "RECREATE");
    TH1F* hist;

    for(int i = 0; i < Nplot; i++){

	cout << "Processing\t" << vars[i] << "\t" << varNames[i] << "\t" << cuts[i] << endl;

	// for debug:
//	cout << "cont[" << i << "] = ";
//	cout << "(\"" << varNames[i] << "\",\"" << vars[i] << "\",\"" << cuts[i] << "\")" << endl;


        TCanvas * canv =  MakePlot(tree,vars[i],varNames[i],cuts[i]);

	hist = (TH1F*)canv->GetPrimitive(varNames[i]);

	// write if exists
	if(hist && hist->GetEntries()){
	    hist->Write();
	    cout << "Writing histo" << endl;
	    canv->SaveAs(prefix+varNames[i]+".pdf");
	}

    }

    fout->Close();
    fp->Close();
}
