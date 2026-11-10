void root_7()
{
	TCanvas *ca = new TCanvas("ca","7-3",600,800);
        TGraph *gr = new TGraph();

        int N = 1000000;
        double A = 197.0;
        double R = 1.18 * pow(A,1.0/3.0) - 0.48;
        double a = 0.54;
        double b_vec[7] = {0.0,1.0,2.0,3.0,4.0,5.0,R};
        double b_max = sqrt(4.2/TMath::Pi());

	TCanvas *c[7];
	TGraph *g[7];

        for (int n = 0; n<7; n=n+1)
        {
                gRandom -> SetSeed();
                double b = b_vec[n];
                int number_A = 0;
                int number_B = 0;
                int wounded_nucleon = 0;
                int participant = 0;
        	double xA_vec[200] = {0};
        	double yA_vec[200] = {0};
        	double xB_vec[200] = {0};
	        double yB_vec[200] = {0};
		double sum_X = 0.0;
		double sum_Y = 0.0;
                double ave_X = 0.0;
                double ave_Y = 0.0;
		double epsilon = 0.0;

                c[n] = new TCanvas(Form("c_%d", n),Form("participant b = %.2f", b) ,600,800);
                g[n] = new TGraph();

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
                                int n1 = g[n]->GetN();
                                g[n] -> SetPoint(n1,xA_vec[j],yA_vec[j]);

				sum_X = sum_X + xA_vec[j]*xA_vec[j];
                                sum_Y = sum_Y + yA_vec[j]*yA_vec[j];

                        }
                }
	c[n] ->cd();
        g[n] ->SetTitle("x-y;x[fm];y[fm]");
        g[n] ->SetMarkerStyle(20);
        g[n] ->Draw("AP");

	ave_X = sum_X/197;
	ave_Y = sum_Y/197;
	epsilon = (ave_X*ave_X - ave_Y*ave_Y)/(ave_X*ave_X + ave_Y*ave_Y);
	int n2 = gr->GetN();
	gr -> SetPoint(n2,b,epsilon);

        }

	ca ->cd();
        gr ->SetTitle("epsilon;b[fm];epsilon[fm]");
        gr ->SetMarkerStyle(20);
        gr ->Draw("APL");

}
