void comparisonPlots(std::string fileName1, std::string fileName2) {

  TFile *file1 = new TFile(fileName1.c_str());
  TFile *file2 = new TFile(fileName2.c_str());

  if(file1->GetNkeys() != file2->GetNkeys()) {
    std::cerr << "Files are dissimilar - can not be compared" << std::endl;
  }

  TIter next1(file1->GetListOfKeys());
  TIter next2(file2->GetListOfKeys());

  // Loop over directories

  TKey *key1;
  TKey *key2;

  while( ( key1 = (TKey*) next1(), key2 = (TKey*) next2() ) ) {

    auto dir1 = (TDirectoryFile*) file1->Get(key1->GetName());
    auto dir2 = (TDirectoryFile*) file2->Get(key2->GetName());

    TIter nextTree1(dir1->GetListOfKeys());
    TIter nextTree2(dir2->GetListOfKeys());

    TKey *treeKey1;
    TKey *treeKey2;

    while( ( treeKey1 = (TKey*) nextTree1(), treeKey2 = (TKey*) nextTree2() ) ) {

      auto tree1 = (TTree*) dir1->Get(treeKey1->GetName());
      auto tree2 = (TTree*) dir2->Get(treeKey2->GetName());

      tree1->SetLineColor(kRed);
      tree2->SetLineColor(kBlue);
      
      TIter nextLeaf1(tree1->GetListOfLeaves());
      TIter nextLeaf2(tree2->GetListOfLeaves());

      TLeaf *leaf1;
      TLeaf *leaf2;

      while( ( leaf1 = (TLeaf*) nextLeaf1(), leaf2 = (TLeaf*) nextLeaf2() ) ) {

	std::string stackName(tree1->GetName());
	stackName += "-";
	stackName += leaf1->GetName();

	std::string hist1Name = stackName + "1";
	TH1F *hist1 = new TH1F(hist1Name.c_str(), leaf1->GetName(), 100, 1, 0); // auto-bin
	tree1->Project(hist1Name.c_str(), leaf1->GetName());
	hist1->Scale(1./hist1->Integral());
	hist1->SetLineColor(kRed);

	std::string hist2Name = stackName + "2";
	TH1F *hist2 = new TH1F(hist2Name.c_str(), leaf1->GetName(), 100, 1, 0); // auto-bin
	tree2->Project(hist2Name.c_str(), leaf2->GetName());
	hist2->Scale(1./hist2->Integral());
	hist2->SetLineColor(kBlue);

	THStack *stack = new THStack(stackName.c_str(), leaf1->GetName());
	stack->Add(hist1);
	stack->Add(hist2);

	TCanvas *canvas = new TCanvas();
	stack->Draw("nostack");
	TLegend *lg=new TLegend(0.5,0.5,0.75,0.65);
	lg->AddEntry(hist1, file1->GetName(), "l");
	lg->AddEntry(hist2, file2->GetName(), "l");
	lg->Draw();

	std::string fileName = stackName + ".png";
	canvas->SaveAs(fileName.c_str());

      }

    }

  }

}
