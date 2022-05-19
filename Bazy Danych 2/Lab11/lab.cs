using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Lab11
{
    class Marka
    {
        public int ID { get; set; }
        public String Nazwa { get; set; }
    }

    class ModelParam
    {
        public int Id { get; set; }
        public String fuelType { get; set; }
        public Int32 enginePower { get; set; }
        public Int32 engineTorque { get; set; }
    }

    class Model
    {
        public int Id
        {
            get { return rId; }
            set { rId = value; }
        }
        public String name { get; set; }
        public Int32 refMarka { get; set; }
        public List<ModelParam> prop { get; set; }
        private int rId;
    }

    class Program
    {
        static void Main(string[] args)
        {
            List<Marka> marki = new List<Marka>
            {
                new Marka{ ID = 1, Nazwa = "Fiat"},
                new Marka{ ID = 2, Nazwa = "BMW"},
                new Marka{ ID = 3, Nazwa = "Peugeot"},
                new Marka{ ID = 4, Nazwa = "Volkswagen"},
                new Marka{ ID = 5, Nazwa = "Toyota"},
                new Marka{ ID = 6, Nazwa = "Mazda"},
                new Marka{ ID = 7, Nazwa = "Seat"}
            };

            ModelParam par1 = new ModelParam() { Id = 1, fuelType = "Petrol", enginePower = 110, engineTorque = 130 };
            ModelParam par2 = new ModelParam() { Id = 2, fuelType = "Petrol", enginePower = 170, engineTorque = 290 };
            ModelParam par3 = new ModelParam() { Id = 3, fuelType = "Diesel", enginePower = 140, engineTorque = 280 };
            ModelParam par4 = new ModelParam() { Id = 4, fuelType = "Diesel", enginePower = 190, engineTorque = 320 };

            List<Model> models = new List<Model>
            {
                new Model{ Id = 1, name = "CX5", refMarka = 6, prop = new List<ModelParam> {par1, par3} },
                new Model{ Id = 2, name = "Corolla", refMarka = 5, prop = new List<ModelParam> {par2, par3}  },
                new Model{ Id = 3, name = "Leon", refMarka = 7, prop = new List<ModelParam> {par2, par4} }
            };

            Console.WriteLine("------------------------------------------");
            Console.WriteLine("Zadanie 1.");
            var query1 = from marka in marki
                         join model in models on marka.ID equals model.Id
                         select new { marka.Nazwa, model.prop };
            foreach (var q1 in query1)
            {
                string brandName = q1.Nazwa;
                foreach (var p in q1.prop)
                {
                    string fuelType = p.fuelType;
                    Int32 engineTorque = p.engineTorque;
                    Console.WriteLine(brandName + " : " + engineTorque + " : " + fuelType);
                }
            }

            Console.WriteLine("------------------------------------------");
            Console.WriteLine("Zadanie 2.");
            var query2 = from marka in marki
                         join model in models on marka.ID equals model.Id
                         orderby marka.Nazwa, model.name
                         select new { marka.Nazwa, model.name, model.prop };

            foreach (var q2 in query2)
            {
                string brandName = q2.Nazwa;
                string modelName = q2.name;
                foreach (var p in q2.prop)
                {
                    string fuelType = p.fuelType;
                    Int32 enginePower = p.enginePower;

                    Console.WriteLine(brandName + " : " + modelName + " : " + fuelType + " : " + enginePower);
                }
            }

            Console.WriteLine("------------------------------------------");
            Console.WriteLine("Zadanie 3.");
            var query3 = from model in models
                         from modelParam in model.prop
                         where modelParam.fuelType == "Petrol"
                         join marka in marki on model.Id equals marka.ID
                         group marka by marka.Nazwa into modelGroup
                         select new { nazwa = modelGroup.Key, benzyniaki = modelGroup.Count() };

            foreach (var q3 in query3)
            {
                Console.WriteLine(q3.nazwa + " : " + q3.benzyniaki);
            }

            Console.ReadKey();
        }
    }
}

