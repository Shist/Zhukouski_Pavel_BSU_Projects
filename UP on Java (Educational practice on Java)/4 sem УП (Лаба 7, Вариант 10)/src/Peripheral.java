import java.util.Objects;

public class Peripheral
{ // Класс "Периферийные устройства"
	final String Name;
	final int ID_Manufact_City;
	final int ID_Manufact_Street;
	final int Year_of_Creating;
	final int ID_Supplier;

	public Peripheral(String Name,
					int ID_Manufact_City,
					int ID_Manufact_Street,
					int Year_of_Creating,
					int ID_Supplier)
	{
		this.Name = Name;
		this.ID_Manufact_City = ID_Manufact_City;
		this.ID_Manufact_Street = ID_Manufact_Street;
		this.Year_of_Creating = Year_of_Creating;
		this.ID_Supplier = ID_Supplier;
	}

	public int getcity()
	{
		return ID_Manufact_City;
	}

	public int getYear()
	{
		return Year_of_Creating;
	}

	public int getstreet()
	{
		return ID_Manufact_Street;
	}

	public int getSupplier() {return ID_Supplier; }

	public String getName()
	{
		return Name;
	}

	@Override
	public int hashCode()
	{
		return Objects.hash(ID_Manufact_City, ID_Manufact_Street, Year_of_Creating, ID_Supplier);
	}
}