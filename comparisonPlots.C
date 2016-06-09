void comparisonPlots(std::string fileName1, std::string fileName2) {

  TFile *file1 = new TFile(fileName1.c_str());
  TFile *file2 = new TFile(fileName2.c_str());

  if(file1->GetNkeys() != file2->GetNkeys()) {
    std::cerr << "Files are dissimilar - can not be compared" << std::endl;
  }

  file1->ls();
  file2->ls();

  TIter next1(file1->GetListOfKeys());
  TIter next2(file2->GetListOfKeys());

  // Loop over directories

  TKey *key1;
  TKey *key2;

  while( ( key1 = (TKey*) next1(), key2 = (TKey*) next2() ) ) {

    std::cout << key1->GetClassName() << " / " << key1->GetName()<< std::endl;
    std::cout << key2->GetClassName() << " / " << key2->GetName()<< std::endl;

    auto dir1 = (TDirectoryFile*) file1->Get(key1->GetName());
    auto dir2 = (TDirectoryFile*) file2->Get(key2->GetName());

    dir1->ls();
    dir2->ls();

    TIter nextTree1(dir1->GetListOfKeys());
    TIter nextTree2(dir2->GetListOfKeys());

    TKey *treeKey1;
    TKey *treeKey2;

    while( ( treeKey1 = (TKey*) nextTree1(), treeKey2 = (TKey*) nextTree2() ) ) {

      std::cout << treeKey1->GetClassName() << " / " << treeKey1->GetName()<< std::endl;
      std::cout << treeKey2->GetClassName() << " / " << treeKey2->GetName()<< std::endl;

      auto tree1 = (TTree*) dir1->Get(treeKey1->GetName());
      auto tree2 = (TTree*) dir2->Get(treeKey2->GetName());

      tree1->ls();
      tree2->ls();
      
      tree1->SetLineColor(kRed);
      tree2->SetLineColor(kBlue);
      
      TIter nextLeaf1(tree1->GetListOfLeaves());
      TIter nextLeaf2(tree2->GetListOfLeaves());

      TLeaf *leaf1;
      TLeaf *leaf2;

      while( ( leaf1 = (TLeaf*) nextLeaf1(), leaf2 = (TLeaf*) nextLeaf2() ) ) {

	std::cout << leaf1->GetName()<< std::endl;
	std::cout << leaf2->GetName()<< std::endl;

	TCanvas *canvas = new TCanvas();
	TLegend *lg=new TLegend(0.55,0.55,0.85,0.85);
	tree1->Draw(leaf1->GetName());
	lg->AddEntry(tree1, file1->GetName(), "l");
	tree2->Draw(leaf2->GetName(), "", "SAME");
	lg->AddEntry(tree2, file2->GetName(), "l");
	lg->Draw();
	std::string fileName(tree1->GetName());
	fileName += "-";
	fileName += leaf1->GetName();
	fileName += ".png";
	canvas->SaveAs(fileName.c_str());

      }

    }

  }

}
