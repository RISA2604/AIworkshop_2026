void root_6()
{
        int N = 1000000;
        double A = 197.0;
        double R = 1.18 * pow(A,1.0/3.0) - 0.48;
        double a = 0.54;
	double b_vec[4] = {0.0,2.0,4.0,8.0};
        double b_max = sqrt(4.2/TMath::Pi());
        TCanvas *c[12];
        TH1F *h[12];
        gRandom -> SetSeed();

	for (int n = 0; n<2; n=n+1)
	{
                double b = b_vec[n];

                c[3*n] = new TCanvas(Form("c_%d", 3*n),Form("b = %.2f", b) ,600,800);
                c[3*n+1] = new TCanvas(Form("c_%d", 3*n+1),Form("b = %.2f", b) ,600,800);
                c[3*n+2] = new TCanvas(Form("c_%d", 3*n+2),Form("b = %.2f", b) ,600,800);
	        h[3*n] = new TH1F(Form("h_%d", 3*n),Form("wounded_nucleon"),100, 0, 1500);
                h[3*n+1]  = new TH1F(Form("h_%d", 3*n+1),Form("participant"),197,0,200);
                h[3*n+2]  = new TH1F(Form("h_%d", 3*n+2),Form("spector"),197,0,200);

	for (int m = 0; m<10000; m=m+1)
	{
	        int number_A = 0;
	        int number_B = 0;
	        int wounded_nucleon = 0;
	        int participant = 0;
                double xA_vec[200] = {0};
                double yA_vec[200] = {0};
                double xB_vec[200] = {0};
                double yB_vec[200] = {0};

        	for (int i = 0; i<N; i=i+1)
        	{
			if (number_A < 197)
			{
	                	double xA = 20*(gRandom -> Rndm()*2.0-1.0);
		                double yA = 20*(gRandom -> Rndm()*2.0-1.0);
		                double zA = 20*(gRandom -> Rndm()*2.0-1.0);

	        	        double rA = sqrt(xA*xA + yA*yA + zA*zA);
        	        	double rho_A = 1.0/(1.0 + exp((rA-R)/a));
				double uA = gRandom ->Rndm();
	                	if (uA < rho_A)
      		          	{
                                        xA_vec[number_A] = xA - b/2.0;
                                        yA_vec[number_A] = yA;
					number_A = number_A + 1;
				}
			}

			if (number_B < 197)
			{
                		double xB = 20*(gRandom -> Rndm()*2.0-1.0);
                		double yB = 20*(gRandom -> Rndm()*2.0-1.0);
                		double zB = 20*(gRandom -> Rndm()*2.0-1.0);

                		double rB = sqrt(xB*xB + yB*yB + zB*zB);
                		double rho_B = 1.0/(1.0 + exp((rB-R)/a));
                		double uB = gRandom ->Rndm();

                		if (uB < rho_B)
                		{
                                        xB_vec[number_B] = xB + b/2.0;
                                        yB_vec[number_B] = yB;
					number_B = number_B + 1;
				}

			}

                	if (number_A == 197 && number_B == 197)
                	{
                        	break;
                	}

		}


		for (int j = 0; j<197; j=j+1)
		{
                	bool hit = false;
        		for (int i = 0; i<197; i=i+1)
			{
				double X = xA_vec[j] - xB_vec[i];
				double Y = yA_vec[j] - yB_vec[i];
				double d = sqrt(X*X + Y*Y);
                		if (d < b_max)
                		{
                			wounded_nucleon = wounded_nucleon + 1;
					hit = true;
               	 		}

        		}

                	if (hit == true)
                	{
                		participant = participant + 1;
                	}
		}

		int spector = 197 - participant;

//		cout << "b = " << b << endl;
//        	cout << "wounded nucleon = " << wounded_nucleon << endl;
//        	cout << "participant =  " << participant << endl;
//        	cout << "spector = " << spector << endl;

                h[3*n] -> Fill(wounded_nucleon);
                h[3*n+1] -> Fill(participant);
                h[3*n+2] -> Fill(spector);
	}

        c[3*n] ->cd();
        h[3*n] ->Draw();
        c[3*n+1] ->cd();
        h[3*n+1] ->Draw();
        c[3*n+2] ->cd();
        h[3*n+2] ->Draw();
	}
}
