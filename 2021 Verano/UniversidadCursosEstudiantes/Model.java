import java.util.List;
import java.util.ArrayList;

public class Model{
	private Universidad universidad;
	
	public Model(){
		this.universidad = new Universidad("Universidad Nacional");
	}
	
	public Universidad getUniversidad(){
		return universidad;
	}
	
	public void setUniversidad(Universidad universidad){
		this.universidad = universidad;
	}
	
}