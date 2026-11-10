void root_2()
{
	TCanvas *c1 = new TCanvas("c1","pi",800,600);
	c1->SetLogx();

	TGraphErrors *g1 = new TGraphErrors();

	for (int a = 0; a < 6; a = a+1)
	{
	double pi_sum = 0;
        double N = pow(10,a+1);
	double pi_data[15];

		for (int s = 0; s < 10; s = s+1)
		{

        	gRandom->SetSeed(0);
                int count = 0;
			for (int i = 0; i < N; i = i+1)
			{
				double x = gRandom->Rndm()*2.0-1.0;
				double y = gRandom->Rndm()*2.0-1.0;

				if (x*x + y*y <= 1.0)
				count = count + 1;
			}
		double pi = 4.0 * count / N;
		pi_data[s] = pi;
		pi_sum = pi_sum + pi;
		}
	double pi_ave = pi_sum / 10.0;
        cout << "pi = " << pi_ave << endl;



	double var = 0;
		for (int s=0; s<10; s = s+1)
		{
			var = var + (pi_data[s] - pi_ave)*(pi_data[s] - pi_ave);
		}
	double sd = sqrt(var / 10.0);
	double se = sd / sqrt(10.0);
	cout << "se = " << se << endl;


	g1->SetPoint(a, N, pi_ave);
	g1->SetPointError(a, 0, se);
	}

	g1->SetTitle("pi;random number;number pi");
	g1->SetMarkerStyle(20);
	g1->SetMarkerSize(2);
	g1->Draw("AP");

	TLine *line = new TLine(0,3.1415926535,1000000,3.1415926535);
	line->SetLineColor(kRed);
	line->SetLineStyle(2);
	line->SetLineWidth(2);
	line->Draw("same");

	c1->SaveAs("root_2.png");
}
