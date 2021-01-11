using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;
using System.Xml.Schema;

namespace xml_doc
{
  class Program {
    static void displayTree(XmlNode node, int level) {
      if (node.Name == "#text") {
        Console.WriteLine(node.Value);
        return;
      }
      Console.WriteLine("Level {0}, node name: {1}", level, node.Name);
      if (node.Attributes != null) {
        for (int i = 0; i < node.Attributes.Count; i++)
          Console.WriteLine("\t attribute {0}, name = {1}, value = {2}", i, node.Attributes[i].Name, node.Attributes[i].Value); 
      }
      if (node.ChildNodes != null) {
        for (int i = 0; i < node.ChildNodes.Count; i++)
          displayTree(node.ChildNodes[i], level + 1);
      }
    }

    static void myValidationHandler(object sender, ValidationEventArgs e) {
      switch (e.Severity)
      {
        case XmlSeverityType.Error:
          Console.WriteLine("Error: {0}", e.Message);
          break;
        case XmlSeverityType.Warning:
          Console.WriteLine("Warning {0}", e.Message);
          break;
      }
    }

        static void Main(string[] args)
        {
          XmlDocument xd = new XmlDocument();
          XmlReaderSettings settings = new XmlReaderSettings();
          settings.DtdProcessing = DtdProcessing.Parse;
          settings.ValidationType = ValidationType.DTD;
          using (XmlReader reader = XmlReader.Create("problems.xml", settings)) {
            try
            {
              xd.Load(reader);
            }
            catch (XmlSchemaException ex)
            {
              Console.WriteLine(ex.Message);
              return;
            }
          }
          XmlNode root = xd.DocumentElement;
          displayTree(root, 0);
        }
    }
}
