void dumpPlots(std::string fileName) {

  TFile *file = new TFile(fileName.c_str());

  TIter next(file->GetListOfKeys());

  // Loop over directories

  TKey *key;

  while( (key = (TKey*) next()) ) {

    std::cout << key->GetClassName() << " / " << key->GetName()<< std::endl;

    auto dir = (TDirectoryFile*) file->Get(key->GetName());

    TIter nextTree(dir->GetListOfKeys());

    TKey *treeKey;

    while( (treeKey = (TKey*) nextTree()) ) {

      std::cout << treeKey->GetClassName() << " / " << treeKey->GetName()<< std::endl;

      auto tree = (TTree*) dir->Get(treeKey->GetName());

      tree->ls();
      
      tree->SetLineColor(kRed);
      
      TIter nextLeaf(tree->GetListOfLeaves());

      TLeaf *leaf;

      while( (leaf = (TLeaf*) nextLeaf()) ) {

	std::cout << leaf->GetName()<< std::endl;

	TCanvas *canvas = new TCanvas();
	tree->Draw(leaf->GetName());
	std::string fileName(tree->GetName());
	fileName += "-";
	fileName += leaf->GetName();
	fileName += ".png";
	canvas->SaveAs(fileName.c_str());

      }

    }

  }

}
