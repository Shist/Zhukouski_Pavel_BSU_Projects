using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;

namespace xml
{
    class Program
    {
        static void Main(string[] args)
        {
            XmlReaderSettings rsettings = new XmlReaderSettings();
            rsettings.DtdProcessing = DtdProcessing.Parse;
            rsettings.ValidationType = ValidationType.DTD;
            using (XmlReader reader = XmlReader.Create("problems.xml", rsettings))
            {
                while (reader.Read())
                {
                    switch (reader.NodeType)
                    {
                        case XmlNodeType.Element:
                            Console.WriteLine("<{0}> contains {1} attribute(s): {2}", reader.Name, reader.AttributeCount, reader.Value);
                            for (int i = 0; i < reader.AttributeCount; i++)
                            {
                                reader.MoveToNextAttribute();
                                Console.WriteLine("   Attribute name = {0}, attribute value = {1}", reader.Name, reader.Value);
                            }
                            reader.MoveToElement();
                            break;
                        case XmlNodeType.Text:
                            Console.WriteLine(reader.Value);
                            break;
                        //case XmlNodeType.CDATA:
                        //    Console.WriteLine("<![CDATA[{0}]]>", reader.Value);
                        //    break;
                        //case XmlNodeType.ProcessingInstruction:
                        //    Console.WriteLine("<?{0} {1}?>", reader.Name, reader.Value);
                        //    break;
                        //case XmlNodeType.Comment:
                        //    Console.WriteLine("<!--{0}-->", reader.Value);
                        //    break;
                        case XmlNodeType.XmlDeclaration:
                            Console.WriteLine("<?xml version='1.0'?>");
                            break;
                        //case XmlNodeType.Document:
                        //    break;
                        //case XmlNodeType.DocumentType:
                        //    Console.WriteLine("<!DOCTYPE {0} [{1}]", reader.Name, reader.Value);
                        //    break;
                        //case XmlNodeType.EntityReference:
                        //    Console.WriteLine(reader.Name);
                        //    break;
                        case XmlNodeType.EndElement:
                            Console.WriteLine("</{0}>", reader.Name);
                            break;
                    }

                }
            }

            XmlWriterSettings settings = new XmlWriterSettings();
            settings.Indent = true;
            settings.Encoding = Encoding.Default;
            using (XmlWriter writer = XmlWriter.Create("example.xml", settings))
            {
                writer.WriteStartDocument();
                writer.WriteStartElement("taskset");
                    writer.WriteStartElement("task");
                    writer.WriteAttributeString("name", "Химия");
                    writer.WriteAttributeString("shortName", "chemistry");
                    writer.WriteString("\nПервая задача отбора к олимпиаде ФПМИ\n");
                        writer.WriteStartElement("metafile");
                        writer.WriteAttributeString("name", "chemistry.in");
                        writer.WriteAttributeString("type", "input");
                        writer.WriteAttributeString("alias", "in");
                        writer.WriteEndElement();
                        writer.WriteWhitespace("");
                        writer.WriteStartElement("metafile");
                        writer.WriteAttributeString("name", "chemistry.out");
                        writer.WriteAttributeString("type", "output");
                        writer.WriteAttributeString("alias", "out");
                        writer.WriteEndElement();
                    writer.WriteEndElement();
                writer.WriteEndElement();
                writer.WriteEndDocument();
            }
        }
    }
}
