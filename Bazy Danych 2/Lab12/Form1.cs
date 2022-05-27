using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{

    public partial class Form1 : Form
    {
        private EmployeeDataContext db;

        public Form1()
        {
            InitializeComponent();
            db = new EmployeeDataContext();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            //1

            var query1 = from s in db.SalesPersons select s;
            var query2 = from emp in db.employees select emp;

            dataGridView1.DataSource = query1;
            dataGridView2.DataSource = query2;

            //2
            try
            {
                var query3 = from emp in db.employees
                            group emp by emp.DeparmentName into grouped
                            select new
                            {
                                departmentName = grouped.Key,
                                maxSalary = (from t2 in grouped select t2.Rate).Max()
                            } into sorted
                            orderby sorted.maxSalary descending
                            select sorted;



                dataGridView3.DataSource = query3;
            }
            catch (Exception er)
            {
                Console.WriteLine(er);
            }

            //3
            try
            {
                var groupSalary = from emp in db.employees
                                  group emp by emp.DeparmentName into grouped
                                  select new
                                  {
                                      departmentName = grouped.Key,
                                      maxSalary = (from t2 in grouped select t2.Rate).Max()
                                  } into sorted
                                  orderby sorted.maxSalary descending
                                  select sorted;

                var groupNames = from emp in db.employees
                                 select new
                                 {
                                     Name = emp.Name,
                                     departmentName = emp.DeparmentName,
                                     salary = emp.Rate
                                 };

                var query4 = from s in groupSalary
                             join n in groupNames on s.maxSalary equals n.salary
                             select new
                             {
                                 departmentName = s.departmentName,
                                 employeeName = n.Name,
                                 rate = n.salary
                             };
                             

                dataGridView4.DataSource = query4;
            }
            catch (Exception er)
            {
                Console.WriteLine(er);
            }

            //4
            try
            {
                var allEmps = from emp in db.employees
                              select emp.BusinessEntityID;

                var salesEmps = (from sal in db.SalesPersons
                                select sal.BusinessEntityID);

                var nonSalesEmps = ((allEmps).Except(salesEmps)).AsQueryable();

                var query5 = from emp1 in db.employees
                             join emp2 in nonSalesEmps on emp1.BusinessEntityID equals emp2
                             select new
                             {
                                 emp1.Name,
                                 emp1.DeparmentName
                             };


                dataGridView5.DataSource = query5;
            }
            catch (Exception er)
            {
                Console.WriteLine(er);
            }

        }

    }
}
