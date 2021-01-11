using System;
using System.Collections.Generic;
using System.Windows.Forms;
using System.Xml;
using System.Xml.Schema;
using System.IO;
using Newtonsoft.Json.Linq;
using System.Web.Helpers;
using Newtonsoft.Json.Schema;

namespace XML_WfApp
{

    public partial class fXML_Reader : Form
    {
        SortedSet<string> elementsSortSet = new SortedSet<string>();
        string strOfTabulation;
        public fXML_Reader()
        {
            InitializeComponent();
        }

        private string CreateStrOfTabulation(int? amount = null)
        {
            strOfTabulation = "";
            if (amount == null)
                for (int i = 0; i < elementsSortSet.Count - 1; i++)
                    strOfTabulation += "   ";
            else
                for (int i = 0; i < amount; i++)
                    strOfTabulation += "   ";
            return strOfTabulation;
        }

        private void btnXMLReader_Click(object sender, EventArgs e)
        {
            XmlDocument xd = new XmlDocument();
            XmlReaderSettings settings = new XmlReaderSettings();
            settings.DtdProcessing = DtdProcessing.Parse;
            settings.ValidationType = ValidationType.DTD;

            rtbTextInfoOut.Text += "XML READING \n";
            using (XmlReader readerDTD = XmlReader.Create("Library.xml", settings))
            {
                try
                {
                    xd.Load(readerDTD);
                }
                catch (XmlSchemaException ex)
                {
                    rtbTextInfoOut.AppendText(
                        "-------------------------------------------------------------------------------\n"
                        + ex.Message +
                        "\n-------------------------------------------------------------------------------\n");
                    return;
                }
            }
            using (XmlReader reader = new XmlTextReader("Library.xml"))
            {
                while (reader.Read())
                {
                    switch (reader.NodeType)
                    {
                        case XmlNodeType.Element:
                            {
                                elementsSortSet.Add(reader.Name);
                                CreateStrOfTabulation();

                                rtbTextInfoOut.Text += "\n" + strOfTabulation
                                    + string.Format("<{0}> contains {1} attribute(s)\n",
                                reader.Name, reader.AttributeCount);
                                for (int i = 0; i < reader.AttributeCount; i++)
                                {
                                    reader.MoveToNextAttribute();
                                    rtbTextInfoOut.Text += strOfTabulation + string.Format
                                        ("    Attribute name = \"{0}\" attribute value =\"{1}\"\n",
                                        reader.Name, reader.Value);
                                }
                                reader.MoveToNextAttribute();
                                break;
                            }
                        case XmlNodeType.Text:
                            rtbTextInfoOut.Text += strOfTabulation + reader.Value + "\n";
                            break;
                        case XmlNodeType.EndElement:
                            {
                                CreateStrOfTabulation();
                                elementsSortSet.Remove(reader.Name);
                                rtbTextInfoOut.Text += strOfTabulation
                                    + string.Format("</{0}>\n", reader.Name);
                                break;
                            }
                    }
                }
            }
            rtbTextInfoOut.Text += "-----------------------------------------------------------------------------\n";
            rtbTextInfoOut.Text += "\n\n\n";
        }

        private void btnClearRtbTextInfoOut_Click(object sender, EventArgs e)
        {
            rtbTextInfoOut.Clear();
        }

        private static bool DynamicNullCheck(dynamic dynamic)
        {
            if (Object.ReferenceEquals(null, dynamic))
                return true;
            else
                return false;
        }

        private void btnJSONReader_Click(object sender, EventArgs e) {
            string jsonString = null;
            rtbTextInfoOut.Text += "JSON READING \n";
            try
            {
                using (StreamReader r = new StreamReader("Library.json"))
                {
                    jsonString = r.ReadToEnd();
                }
            } catch (Exception ex)
            {
                rtbTextInfoOut.Text += "Reader Exception: " + ex.Message; 
            }

            try
            {
                JObject jo = JObject.Parse(jsonString);
                string schemaString;
                using (StreamReader sr = new StreamReader("LibraryJSON_Validation.json"))
                {
                    schemaString = sr.ReadToEnd();
                }
                JSchema schema = JSchema.Parse(schemaString);
                if (!jo.IsValid(schema, out IList<string> messages))
                {
                    rtbTextInfoOut.Text +=
                        "-------------------------------------------------------------------------------\n";

                    //foreach (var item in messages)
                    //{
                    //    rtbTextInfoOut.Text += item + "\n";
                    //}

                    //rtbTextInfoOut.Text +=
                    //        "-------------------------------------------------------------------------------\n";
                    //if (messages.Count != 0)
                    //    return;
                }
            } catch (Exception ex)
            {
                rtbTextInfoOut.Text += "Validation Exception: " + ex.Message;
            }
            try
            {
                dynamic data = Json.Decode(jsonString);
                for (int i = 0; i < data.bookSet.Length; i++)
                {
                    rtbTextInfoOut.AppendText("Book number:\t" + data.bookSet[i].number + "\n");
                    rtbTextInfoOut.Text += "ISBN:\t" + data.bookSet[i].ISBN + "\n";
                    rtbTextInfoOut.Text += "name:\t" + data.bookSet[i].name + "\n";
                    rtbTextInfoOut.Text += "place:\t" + data.bookSet[i].place + "\n";

                    
                    for (int j = 0; j < data.bookSet[i].author.Length; j++)
                    {
                        rtbTextInfoOut.Text += "author:\t" + data.bookSet[i].author[j].name + "\n";
                    }
                    rtbTextInfoOut.Text += "-------------------------------------------------------------------------------\n";

                    rtbTextInfoOut.Text += "\n";
                }
            } catch (Exception ex)
            {
                rtbTextInfoOut.Text += "JSON Decoding Exception: " + ex.Message;
            }           
        }
    }
}















