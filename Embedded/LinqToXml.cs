using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Xml.Linq;

namespace LinqToXml
{
    internal struct Service
    {
        public String name,
            annotation,
            type,
            version,
            author,
            termsAndConditionsOfUse,
            informationWhenRegisteringUser;

        public Service(string name, string annotation, string type, string version, string author,
            string termsAndConditionsOfUse, string informationWhenRegisteringUser)
        {
            this.name = name;
            this.annotation = annotation;
            this.type = type;
            this.version = version;
            this.author = author;
            this.termsAndConditionsOfUse = termsAndConditionsOfUse;
            this.informationWhenRegisteringUser = informationWhenRegisteringUser;
        }
    }

    class XmlLinqFilterer
    {
        public void SetData(String input, String name, String annotation,
            String type, String version, String author, String termsAndConditionsOfUse,
            String informationWhenRegisteringUser)
        {
            XElement root = XElement.Parse(input);

            IEnumerable<Service> res = from service in root.Descendants("Service")
                where ((name == null || service.Attribute("Name")?.Value == name) &&
                        (annotation == null || service.Attribute("Annotation")?.Value == annotation) &&
                        (type == null || service.Attribute("Type")?.Value == type) &&
                        (version == null || service.Attribute("Version")?.Value == version) &&
                        (author == null || service.Attribute("Author")?.Value == author) &&
                        (termsAndConditionsOfUse == null ||
                         service.Attribute("TermAndConditionsOfUse")?.Value == termsAndConditionsOfUse) &&
                        (informationWhenRegisteringUser == null ||
                         service.Attribute("InformationWhenRegisteringUser")?.Value == informationWhenRegisteringUser)
                    )
                select new Service(service.Attribute("Name")?.Value,
                    service.Attribute("Annotation")?.Value,
                    service.Attribute("Type")?.Value,
                    service.Attribute("Version")?.Value,
                    service.Attribute("Author")?.Value,
                    service.Attribute("TermsAndConditionsOfUse")?.Value,
                    service.Attribute("InformationWhenRegisteringUser")?.Value
                );
            matchedServices = new List<Service>(res);
        }
        public String GetResult()
        {
            String result = new String("");
            foreach (var s in matchedServices)
            {
                result += "Name: " + s.name + '\n' +
                          "Annotation: " + s.annotation + '\n' +
                          "Type: " + s.type + '\n' +
                          "Version: " + s.version + '\n' +
                          "Author: " + s.author + '\n' +
                          "TermsAndConditionsOfUse: " + s.termsAndConditionsOfUse + '\n' +
                          "InformationWhenRegisteringUser: " + s.informationWhenRegisteringUser;
                if (matchedServices.IndexOf(s) != matchedServices.Count - 1)
                {
                    result += "\n\n";
                }
            }
            return result;
        }
        private List<Service> matchedServices = new List<Service>();
    }

    class Program
    {
        static void Main(string[] args)
        {
            // Intentionally empty
        }
    }
}
