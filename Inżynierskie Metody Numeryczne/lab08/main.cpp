#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

#define M_PI 3.14159265358979323846

const int IT_MAX = 5000;

const int nx = 400;
const int ny = 90;
const int i_1 = 200;
const int i_2 = 210;
const int j_1 = 50;
const double delta = 0.01;
const double sigma = 0.1;
const double xA = 0.45;
const double yA = 0.45;

inline double u0_val(double x, double y)
{
    return exp(-(pow(x - xA, 2) + pow(y - yA, 2)) / 2. / pow(sigma, 2)) / (2 * M_PI * pow(sigma, 2));
}

void save_map(std::fstream& file, const std::vector<std::vector<double>>& u);
void velocity_field(std::vector<std::vector<double>> &vx, std::vector<std::vector<double>> &vy, const std::vector<std::vector<double>>& psi, std::string filename1, std::string filename2);
double find_v_max(const std::vector<std::vector<double>> &vx, const std::vector<std::vector<double>> &vy);
void ad(double D, std::string post);

int main()
{
    ad(0.0, "D_0.dat");
    ad(0.1, "D_1.dat");
}

void save_map(std::fstream& file, const std::vector<std::vector<double>>& u)
{
    for (int i=0; i <= nx; i++)
    {
        for (int j=0; j <= ny; j++)
        {
            file << i << " " << j << " " << u[i][j] << std::endl;
        }
        file << std::endl;
    }
}

void velocity_field(std::vector<std::vector<double>> &vx, std::vector<std::vector<double>> &vy, const std::vector<std::vector<double>>& psi, std::string filename1, std::string filename2)
{
    std::fstream out1, out2;

	for (int i = 1; i < nx; i++) {
		for (int j = 1; j < ny; j++) {
			if (i >= i_1 && i <= i_2 && j <= j_1) {}
			else {
				vx[i][j] = (psi[i][j + 1] - psi[i][j - 1]) / (2 * delta);
				vy[i][j] = -(psi[i + 1][j] - psi[i - 1][j]) / (2 * delta);
			}
		}
	}
	for (int j = 0; j <= ny; j++) {
		vx[0][j] = vx[1][j];
		vx[nx][j] = vx[nx - 1][j];
	}
	for (int i = 1; i < nx; i++) {
		vx[i][0] = vy[i][ny] = 0.;
	}
    out1.open(filename1, std::ostream::out);
    out2.open(filename2, std::ostream::out);

    for (int i=0; i <= nx; i++)
    {
        for (int j=0; j <= ny; j++)
        {
            out1 << i << " " << j << " " << vx[i][j] << std::endl;
            out2 << i << " " << j << " " << vy[i][j] << std::endl;
        }
        out1 << std::endl;
        out2 << std::endl;
    }

    out1.close();
    out2.close();
}

double find_v_max(const std::vector<std::vector<double>> &vx, const std::vector<std::vector<double>> &vy)
{
    double v_max = -1.0, v;
    for (int i=0; i <= nx; i++)
    {
        for (int j=0; j <= ny; j++)
        {
            v = sqrt(vx[i][j]*vx[i][j] + vy[i][j]*vy[i][j]);
            if (v > v_max)
                v_max = v;
        }
    }

    return v_max;
}

void ad(double D, std::string post)
{
    double Tks[] = {delta*IT_MAX/5, 2*delta*IT_MAX/5, 3*delta*IT_MAX/5, 4*delta*IT_MAX/5, 5*delta*IT_MAX/5};

    std::fstream in;
    in.open("psi.dat", std::ifstream::in);

    std::vector<std::vector<double>> vx, vy, psi, u0, u1;
    vx.resize(nx+1);
    vy.resize(nx+1);
    psi.resize(nx+1);
    u0.resize(nx+1);
    u1.resize(nx+1);
    for (int i=0; i < nx+1; i++)
    {
        vx[i].resize(ny+1);
        vy[i].resize(ny+1);
        psi[i].resize(ny+1);
        u0[i].resize(ny+1);
        u1[i].resize(ny+1);
    }
    vx[0][0] = vy[0][0] = 0.0;

    int i, j;
    while (in >> i)
    {
        in >> j;
        in >> psi[i][j];
    }

    velocity_field(vx, vy, psi, "wyniki/vx_" + post, "wyniki/vy_" + post);
    double v_max = find_v_max(vx, vy);
    double dt = delta / (4 * v_max);

    for (int i=0; i <= nx; i++)
        for (int j=0; j <= ny; j++)
        {
            u0[i][j] = u0_val(i*delta, j*delta);
            u1[i][j] = u0[i][j];
        }
    std::string filename1 = "wyniki/c_" + post;
    std::string filename2 = "wyniki/xsr_" + post;

    std::fstream out1, out2;
    out1.open(filename1, std::ofstream::out);
    out2.open(filename2, std::ofstream::out);

    std::fstream map1, map2, map3, map4, map5;
    map1.open("wyniki/Tk1_" + post, std::ofstream::out);
    map2.open("wyniki/Tk2_" + post, std::ofstream::out);
    map3.open("wyniki/Tk3_" + post, std::ofstream::out);
    map4.open("wyniki/Tk4_" + post, std::ofstream::out);
    map5.open("wyniki/Tk5_" + post, std::ofstream::out);

    double M = (1.0 / (1.0 + ((2.0 * D * dt) / pow(delta, 2))));

    for (int it=1; it <= IT_MAX; it++)
    {
        double c = 0.0;
        double x_sr = 0.0;
        for (int k=1; k <= 20; k++)
        {
            for (int i=0; i <= nx; i++)
            {
                for (int j=1; j < ny; j++)
                {
					if (i >= i_1 && i <= i_2 && j <= j_1) {}
					else
                    {
						int ip,il;
						ip=i+1;
						if(i==nx) ip=0;
						il=i-1;
						if(i==0) il=nx;
						u1[i][j]=M*( 
							u0[i][j]
							- dt/2*vx[i][j]*((u0[ip][j]-u0[il][j])/2/delta+(u1[ip][j]-u1[il][j])/2/delta )
							- dt/2*vy[i][j]*((u0[i][j+1]-u0[i][j-1])/2/delta+(u1[i][j+1]-u1[i][j-1])/2/delta )
							+ dt*D/2*( 
								          (u0[ip][j]+u0[il][j]+u0[i][j+1]+u0[i][j-1]-4*u0[i][j])/delta/delta
										  +(u1[ip][j]+u1[il][j]+u1[i][j+1]+u1[i][j-1])/delta/delta )
						);
					}
                }
            }
        }
        for (int i = 0; i <= nx; i++)
        {
			for (int j = 0; j <= ny; j++)
            {
				u0[i][j] = u1[i][j];
				c += u0[i][j] * pow(delta, 2);
				x_sr += i * delta * u0[i][j] * pow(delta, 2);
			}
		}

        out1 << it << " " << c << std::endl;
        out2 << it << " " << x_sr << std::endl;
    
        /*
        if (it == (int)Tks[0])
            save_map(map1, u1);
        else if (it == (int)Tks[1])
            save_map(map2, u1);
        else if (it == (int)Tks[2])
            save_map(map3, u1);
        else if (it == (int)Tks[3])
            save_map(map4, u1);
        else if (it == (int)Tks[4])
            save_map(map5, u1);
        */

       if(D != 0){
			if(it == 1000){
				for (int i = 0; i <= nx; i++) {
					for (int j = 0; j <= ny; j++) {
						map1<<i<<"\t"<<j<<"\t"<<u1[i][j]<<std::endl;
					}
					map1<<std::endl;
				}
			}
			if(it == 2000){
				for (int i = 0; i <= nx; i++) {
					for (int j = 0; j <= ny; j++) {
						map2<<i<<"\t"<<j<<"\t"<<u1[i][j]<<std::endl;
					}
					map2<<std::endl;
				}
			}
			if (it == 3000){
				for (int i = 0; i <= nx; i++) {
					for (int j = 0; j <= ny; j++) {
						map3<<i<<"\t"<<j<<"\t"<<u1[i][j]<<std::endl;
					}
					map3<<std::endl;
				}
			}
			if (it == 4000){
				for (int i = 0; i <= nx; i++) {
					for (int j = 0; j <= ny; j++) {
						map4<<i<<"\t"<<j<<"\t"<<u1[i][j]<<std::endl;
					}
					map4<<std::endl;
				}
			}
			if (it == 5000){
				for (int i = 0; i <= nx; i++) {
					for (int j = 0; j <= ny; j++) {
						map5<<i<<"\t"<<j<<"\t"<<u1[i][j]<<std::endl;
					}
					map5<<std::endl;
				}
			}
		}
    }

    out1.close();
    out2.close();
    map1.close();
    map2.close();
    map3.close();
    map4.close();
    map5.close();
}
