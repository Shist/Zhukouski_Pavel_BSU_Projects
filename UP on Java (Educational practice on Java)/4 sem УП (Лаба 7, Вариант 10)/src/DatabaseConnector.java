import javax.swing.table.*;
import java.sql.*;
import java.util.*;

public class DatabaseConnector
	implements AutoCloseable
{
	private static final String DRIVER = "org.apache.derby.jdbc.EmbeddedDriver";
	private static final String CONNECT = "jdbc:derby:MonumentsDB;create=true";

	private static final String CITIES_INSERT = "INSERT INTO Cities(Name) VALUES (?)";
	private static final String STREETS_INSERT = "INSERT INTO Streets(Name) VALUES (?)";
	private static final String SUPPLIERS_INSERT = "INSERT INTO Publishers(Name) VALUES (?)";
	private static final String PERIPHERALS_INSERT = "INSERT INTO Monuments(Name, CityID , StreetID, " +
		"Year_m, PublisherID) VALUES (?, ?, ?, ?, ?)";

	private static final String CITIES_SELECT = "SELECT * FROM Cities";
	private static final String STREETS_SELECT = "SELECT * FROM Streets";
	private static final String SUPPLIERS_SELECT = "SELECT * FROM Publishers";
	private static final String PERIPHERALS_SELECT =
		"SELECT Monuments.Name, Year_m AS \"Creating year\", " +
			"Cities.Name As \"City\", Streets.Name As \"Street\", " +
			"Publishers.Name As \"Publisher\" " +
			"FROM ((Monuments INNER JOIN Cities " +
			"ON Monuments.CityID = Cities.ID) INNER JOIN Streets " +
			"ON Monuments.StreetID = Streets.ID) INNER JOIN Publishers " +
			"ON Monuments.PublisherID = Publishers.ID";

	private static final String[] INSERT_QUERIES =
		{ CITIES_INSERT, STREETS_INSERT,
		  SUPPLIERS_INSERT, PERIPHERALS_INSERT };
	private static final String[] SELECT_QUERIES =
		{ CITIES_SELECT, STREETS_SELECT,
		  SUPPLIERS_SELECT, PERIPHERALS_SELECT };
		
	
	private Connection connection;
	
	public DatabaseConnector()
	{
		System.setProperty("derby.system.home", "C:\\Users\\user\\IdeaProjects\\4 sem УП (Лаба 7, Вариант 10)\\db");

		try
		{
			Class.forName(DRIVER);
			connection = DriverManager.getConnection(CONNECT);
		}
		catch (Exception ex)
		{
			throw new RuntimeException(ex);
		}
	}

	@Override
	public void close() throws Exception
	{
		connection.close();
	}

	public void insertInTable(Table table, Object data)
	{
		try
		{
			PreparedStatement preparedStatement =
				connection.prepareStatement(INSERT_QUERIES[table.ordinal()]);
			switch (table)
			{
				case Manufacture_Cities:
				case Manufacture_Streets:
				case Suppliers:
					preparedStatement.setString(1, (String)data);
					break;
				case Peripherals:
					Peripheral item = (Peripheral) data;
					preparedStatement.setString(1, item.Name);
					preparedStatement.setInt(2, item.ID_Manufact_City);
					preparedStatement.setInt(3, item.ID_Manufact_Street);
					preparedStatement.setInt(4, item.Year_of_Creating);
					preparedStatement.setInt(5, item.ID_Supplier);
					break;
			}
			preparedStatement.execute();
			preparedStatement.close();
		}
		catch (Exception ex)
		{
			throw new RuntimeException(ex);
		}
	}

	public TableModel selectTable(Table table)
	{
		try
		{
			Statement statement = connection.createStatement();
			ResultSet set;
			try
			{
				set = statement.executeQuery(SELECT_QUERIES[table.ordinal()]);
			}
			catch (SQLException ex)
			{
				return new DefaultTableModel(new Object[0][0], new Object[0]);
			}

			Object[] names = new Object[0];
			ArrayList<Object[]> data = new ArrayList<>();

			switch (table)
			{
				case Manufacture_Cities:
				case Manufacture_Streets:
				case Suppliers:
					names = new Object[] { "ID объекта", "Название объекта" };
					while (set.next())
						data.add(new Object[] { set.getInt("ID"),
												set.getString("Name") });
					break;
				case Peripherals:
					names = new Object[] { "Название устройства", "Город производитель",
										   "Улица производства", "Год создания", "Поставщик" };
					while (set.next())
						data.add(new Object[] { set.getString("Name"),
												set.getString("City"),
												set.getString("Street"),
												set.getInt("Creating year"),
												set.getString("Publisher") } );
					break;
			}
			set.close();
			statement.close();

			Object[][] twoDimData = new Object[data.size()][data.get(0).length];
			for (int i = 0; i < data.size(); ++i)
				System.arraycopy(data.get(i), 0, twoDimData[i], 0, data.get(i).length);

			return new DefaultTableModel(twoDimData, names);
		}
		catch (Exception ex)
		{
			throw new RuntimeException(ex);
		}
	}
}
