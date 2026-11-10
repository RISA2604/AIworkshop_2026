#include <vector>

void root_8()
{
        int N = 1000000;
        double A = 197.0;
        double R = 1.18 * pow(A,1.0/3.0) - 0.48;
        double a = 0.54;
        double b_vec[2] = {0.0,R};
        double b_max = sqrt(4.2/TMath::Pi());

        std::vector<double> hit_xA;
        std::vector<double> hit_yA;
        std::vector<double> hit_xB;
        std::vector<double> hit_yB;

        TCanvas *c[2];
        TGraph *g_A[2];
	TGraph *g_notA[2];
	TGraph *g_B[2];
	TGraph *g_notB[2];

        for (int n = 0; n<2; n=n+1)
        {
                gRandom -> SetSeed();
                double b = b_vec[n];
                int number_A = 0;
                int number_B = 0;
                double xA_vec[200] = {0};
                double yA_vec[200] = {0};
                double xB_vec[200] = {0};
                double yB_vec[200] = {0};
		hit_xA.clear();
                hit_yA.clear();
                hit_xB.clear();
                hit_yB.clear();
		double sum_xA = 0.0;
                double sum_yA = 0.0;
                double sum_xB = 0.0;
                double sum_yB = 0.0;
		double Qx = 0.0;
		double Qy = 0.0;

                c[n] = new TCanvas(Form("c_%d", n),Form("participant b = %.2f", b) ,600,600);
                g_A[n] = new TGraph();
		g_notA[n] = new TGraph();
                g_B[n] = new TGraph();
                g_notB[n] = new TGraph();

                double phi = (gRandom -> Rndm()) *2.0*TMath::Pi();
                cout << "phi = " << phi << endl;

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
                                        xA_vec[number_A] = xA - b/2.0 * cos(phi);
                                        yA_vec[number_A] = yA - b/2.0 * sin(phi);
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
                                        xB_vec[number_B] = xB + b/2.0 * cos(phi);
                                        yB_vec[number_B] = yB + b/2.0 * sin(phi);
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
                                        hit = true;
                                }
                        }

                        if (hit == true)
                        {
                                int n1 = g_A[n] ->GetN();
                                g_A[n] -> SetPoint(n1,xA_vec[j],yA_vec[j]);

                                sum_xA = sum_xA + xA_vec[j];
                                sum_yA = sum_yA + yA_vec[j];

				hit_xA.push_back(xA_vec[j]);
                                hit_yA.push_back(yA_vec[j]);
                        }

			else
			{
                                int n1 = g_notA[n] ->GetN();
                                g_notA[n] -> SetPoint(n1,xA_vec[j],yA_vec[j]);
			}
		}

                for (int j = 0; j<197; j=j+1)
                {
                        bool hit = false;
                        for (int i = 0; i<197; i=i+1)
                        {
                                double X = xB_vec[j] - xA_vec[i];
                                double Y = yB_vec[j] - yA_vec[i];
                                double d = sqrt(X*X + Y*Y);
                                if (d < b_max)
                                {
                                        hit = true;
                                }
                        }

                        if (hit == true)
                        {
                                int n1 = g_B[n] ->GetN();
                                g_B[n] -> SetPoint(n1,xB_vec[j],yB_vec[j]);

                                sum_xB = sum_xB + xB_vec[j];
                                sum_yB = sum_yB + yB_vec[j];

                                hit_xB.push_back(xB_vec[j]);
                                hit_yB.push_back(yB_vec[j]);
                        }

                        else
                        {
                                int n1 = g_notB[n] ->GetN();
                                g_notB[n] -> SetPoint(n1,xB_vec[j],yB_vec[j]);
                        }
                }

	double cent_x = (sum_xA + sum_xB)/(hit_xA.size() + hit_xB.size());
        double cent_y = (sum_yA + sum_yB)/(hit_xA.size() + hit_xB.size());
        cout << "cent_x = " << cent_x << endl;
        cout << "cent_y = " << cent_y << endl;

	for (int i = 0; i<hit_xA.size(); i=i+1)
	{
                double phi_Ai = atan2(hit_yA[i] - cent_y ,hit_xA[i] - cent_x);
                Qx = Qx + cos(2*phi_Ai);
		Qy = Qy + sin(2*phi_Ai);
	}

        for (int i = 0; i<hit_xB.size(); i=i+1)
        {
                double phi_Bi = atan2(hit_yB[i] - cent_y ,hit_xB[i] - cent_x);
                Qx = Qx + cos(2*phi_Bi);
                Qy = Qy + sin(2*phi_Bi);
        }

	double phi_RP = (atan2(Qy,Qx))/2.0;
        cout << "phi_RP = " << phi_RP << endl;

	g_A[n] ->GetXaxis() ->SetLimits(-15.0, 15.0);
	g_A[n] ->SetMinimum(-15.0);
        g_A[n] ->SetMaximum(15.0);
        g_A[n] ->SetMarkerStyle(20);
	g_A[n] ->SetMarkerColor(kRed);
        g_A[n] ->SetTitle("x-y;x[fm];y[fm]");

        g_notA[n] ->GetXaxis() ->SetLimits(-15.0, 15.0);
        g_notA[n] ->SetMinimum(-15.0);
        g_notA[n] ->SetMaximum(15.0);
        g_notA[n] ->SetMarkerStyle(20);
        g_notA[n] ->SetMarkerColor(kGray+1);

        g_B[n] ->GetXaxis() ->SetLimits(-15.0, 15.0);
        g_B[n] ->SetMinimum(-15.0);
        g_B[n] ->SetMaximum(15.0);
        g_B[n] ->SetMarkerStyle(20);
        g_B[n] ->SetMarkerColor(kBlue);
        g_B[n] ->SetTitle("x-y;x[fm];y[fm]");

        g_notB[n] ->GetXaxis() ->SetLimits(-15.0, 15.0);
        g_notB[n] ->SetMinimum(-15.0);
        g_notB[n] ->SetMaximum(15.0);
        g_notB[n] ->SetMarkerStyle(20);
        g_notB[n] ->SetMarkerColor(kGray+1);

	c[n] ->cd();
	g_notA[n] ->Draw("AP");
        g_notB[n] ->Draw("P SAME");
        g_A[n] ->Draw("P SAME");
	g_B[n] ->Draw("P SAME");

	}
}
