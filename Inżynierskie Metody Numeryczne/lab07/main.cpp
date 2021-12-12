#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>

const int IT_MAX = 20000;
const double delta = 0.01;
const double ro = 1;
const double mu = 1;
const int nx = 200;
const int ny = 90;
const int i_1 = 50;
const int j_1 = 55;

void wb_psi(std::vector<std::vector<double>> & psi, double Qwe, double Qwy)
{
    for (int j=j_1; j <= ny; j++)
    {
        psi[0][j] = Qwe / (2 * mu);
        psi[0][j] *= pow(delta*j, 3) / 3.0 - pow(delta*j, 2) / 2.0 * (delta*(j_1 + ny)) + pow(delta, 3) * j * j_1 * ny;
    }

    for (int j=0; j <= ny; j++)
    {
        psi[nx][j] = Qwy / (2 * mu) * (pow(delta*j, 3)/3.0 - pow(delta*j, 2) * delta * ny / 2.0);
        psi[nx][j] += (Qwe * pow(delta*j_1, 2) * (-delta*j_1 + 3*delta*ny)) / (12 * mu);
    }

    for (int i=1; i <= nx - 1; i++)
    {
		psi[i][ny] = psi[0][ny];
	}

	for (int i=i_1; i <= nx - 1; i++)
    {
		psi[i][0] = psi[0][j_1];
	}

	for (int j=1; j <= j_1; j++)
    {
		psi[i_1][j] = psi[0][j_1];
	}

	for (int i=1; i <= i_1; i++)
    {
		psi[i][j_1] = psi[0][j_1];
	}
}

void wb_dzeta(std::vector<std::vector<double>> & dzeta, std::vector<std::vector<double>> & psi, double Qwe, double Qwy)
{

	for (int j = j_1; j <= ny; j++)
    {
		dzeta[0][j] = (Qwe / (2 * mu));
        dzeta[0][j] *= ((2 * j * delta) - (j_1 * delta) - (ny * delta));
	}
	
	for (int j = 0; j <= ny; j++)
    {
		dzeta[nx][j] = (Qwy / (2.0 * mu));
        dzeta[nx][j] *= ((2 * j * delta) - (ny * delta));
	}
	
	for (int i = 1; i <= nx - 1; i++)
    {
		dzeta[i][ny] = (2.0 / pow(delta, 2)) * (psi[i][ny-1] - psi[i][ny]);
	}
	
	for (int i = i_1 + 1; i <= nx - 1; i++)
    {
		dzeta[i][0] = (2.0 / pow(delta, 2)) * (psi[i][1] - psi[i][0]);
	}
	
	for (int j = 1; j <= j_1 - 1; j++)
    {
		dzeta[i_1][j] = (2.0 / pow(delta, 2)) * (psi[i_1+1][j] - psi[i_1][j]);
	}

	for (int i = 1; i <= i_1; i++)
    {
		dzeta[i][j_1] = (2.0 / pow(delta, 2)) * (psi[i][j_1+1] - psi[i][j_1]);
	}
	
	dzeta[i_1][j_1] = (dzeta[i_1-1][j_1] + dzeta[i_1][j_1-1]) / 2;
}

void navier_stokes(double Qwe, std::string str)
{
    std::string filename1 = "wyniki/psi_" + str + ".dat";
    std::string filename2 = "wyniki/dzeta_" + str + ".dat";
    std::string filename3 = "wyniki/u_" + str + ".dat";
    std::string filename4 = "wyniki/v_" + str + ".dat";

    double Qwy = 0.0;
    std::vector<std::vector<double>> psi(nx+1), dzeta(nx+1), u(nx+1), v(nx+1);

    for (int i=0; i < nx+1; i++)
    {
        psi[i].resize(ny+1);
        dzeta[i].resize(ny+1);
        u[i].resize(ny+1);
        v[i].resize(ny+1);

        for (int j=0; j < ny+1; j++)
            psi[i][j] = dzeta[i][j] = 0.0;
    }
    
    Qwy = Qwe/pow(delta*ny, 3) * (pow(delta*ny, 3) - pow(delta*j_1, 3) - 3*delta*j_1*pow(delta*ny, 2) + 3*pow(delta*j_1, 2) * delta*ny);
    double omega;
    wb_psi(psi, Qwe, Qwy);
    for (int it=1; it <= IT_MAX; it++)
    {
        if (it < 2000)
            omega = 0.0;
        else
            omega = 1.0;

        for (int i=1; i <= nx-1; i++)
        {
            for (int j=1; j <= ny-1; j++)
            {
                if (j > j_1 || i > i_1)
                {
                    psi[i][j] = 0.25 * (psi[i+1][j] + psi[i-1][j] + psi[i][j+1] + psi[i][j-1] - delta * delta * dzeta[i][j]);
                    dzeta[i][j] = 0.25 * (dzeta[i+1][j] + dzeta[i-1][j] + dzeta[i][j+1] + dzeta[i][j-1]);
                    dzeta[i][j] -= omega * ro / (16 * mu) * ((psi[i][j+1] - psi[i][j-1])*(dzeta[i+1][j]-dzeta[i-1][j]) - (psi[i+1][j] - psi[i-1][j])*(dzeta[i][j+1] - dzeta[i][j-1]));
                }
            }
        }
        
        wb_dzeta(dzeta, psi, Qwe, Qwy);
        double gamma = 0.0;
        int j2 = j_1 + 2;
        for (int i=1; i < nx-1; i++)
        {
            gamma += (psi[i+1][j2] + psi[i-1][j2] + psi[i][j2+1] + psi[i][j2-1] - 4*psi[i][j2] - delta*delta*dzeta[i][j2]);
        }
    }

    for (int i=1; i <= nx-1; i++)
    {
		for (int j=1; j <= ny-1; j++)
        {
			if (j > j_1 || i > i_1) {
				u[i][j] = (psi[i][j+1] - psi[i][j])/delta;
				v[i][j] = -(psi[i+1][j] - psi[i][j])/delta;
			}
		}
	}
    std::ofstream file1, file2, file3, file4;
    file1.open(filename1, std::iostream::out);
    file2.open(filename2, std::iostream::out);
    file3.open(filename3, std::iostream::out);
    file4.open(filename4, std::iostream::out);
    for (int i=1; i <= nx-1; i++)
    {
		for (int j=1; j <= ny-1; j++)
        {
			file1 << i *delta << " " << j*delta << " " << psi[i][j] << std::endl;
			file2 << i *delta << " " << j*delta << " " << dzeta[i][j] << std::endl;
			file3 << i *delta << " " << j*delta << " " << u[i][j] << std::endl;
			file4 << i *delta << " " << j*delta << " " << v[i][j] << std::endl;
		}
	    file1 << std::endl;
	    file2 << std::endl;
	    file3 << std::endl;
	    file4 << std::endl;
	}
	file1.close();
	file2.close();
	file3.close();
	file4.close();


}

int main()
{
    navier_stokes(-1000.0, "1");
    navier_stokes(-4000.0, "2");
    navier_stokes( 4000.0, "3");
    return 0;
}