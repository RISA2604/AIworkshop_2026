void root_4()
{
	TCanvas *c1 = new TCanvas("c1","x-y",600,600);
        TCanvas *c2 = new TCanvas("c2","x-z",600,600);
 	TCanvas *c3 = new TCanvas("c3","r",800,600);
 	TCanvas *c4 = new TCanvas("c4","theta",800,600);
	TCanvas *c5 = new TCanvas("c5","phi",800,600);

	TGraph *g1 = new TGraph();
        TGraph *g2 = new TGraph();

	TH1F *h1 = new TH1F("h1","r_histgram",100,0,8);
        TH1F *h2 = new TH1F("h2","theta_histgram",100,0,5);
        TH1F *h3 = new TH1F("h3","phi_histgram",100,-5,5);

	TGraph *g3 = new TGraph();
        TGraph *g4 = new TGraph();
        TGraph *g5 = new TGraph();

	int N = 1000000;
	double A = 197;
	double R = 1.2 * pow(A,1.0/3.0);
	gRandom -> SetSeed();
	for (int i = 0; i<N; i=i+1)
	{
		double x = 20*(gRandom -> Rndm()*2.0-1.0);
                double y = 20*(gRandom -> Rndm()*2.0-1.0);
                double z = 20*(gRandom -> Rndm()*2.0-1.0);

		if (x*x + y*y + z*z < R*R)
		{
			int n1 = g1->GetN();
			g1 -> SetPoint(n1,x,y);

                        int n2 = g2->GetN();
                        g2 -> SetPoint(n2,x,z);

			double r = sqrt(x*x + y*y + z*z);
                        double theta = acos(z/r);
                        double phi = atan2(y,x);

			h1 -> Fill(r);
			h2 -> Fill(theta);
			h3 -> Fill(phi);
		}

	}

        TF1 *f1 = new TF1("f1","[0]*x*x",0,R);
        f1->SetParameter(0,700);
        f1->SetLineColor(kRed);

	c1 ->cd();
	g1 ->SetTitle("x-y;x[fm];y[fm]");
	g1 ->SetMarkerStyle(20);
	g1 ->Draw("AP");

        c2 ->cd();
        g2 ->SetTitle("x-z;x[fm];z[fm]");
        g2 ->SetMarkerStyle(20);
        g2 ->Draw("AP");

	c3 ->cd();
	h1 ->Draw();
	h1 ->Fit(f1, "R", "", 0,R);

        c4 ->cd();
        h2 ->Draw();
        h2 ->Fit("pol2");

        c5 ->cd();
        h3 ->Draw();
	h3 ->Fit("pol1", "R", "", -3.2, 3.2);

        cout << "f1 =" << f1 ->GetExpFormula("p") << endl;
        TF1 *f2 = h2 ->GetFunction("pol2");
        cout << "f2 =" << f2 ->GetExpFormula("p") << endl;
        TF1 *f3 = h3 ->GetFunction("pol1");
        cout << "f3 =" << f3 ->GetExpFormula("p") << endl;
}
