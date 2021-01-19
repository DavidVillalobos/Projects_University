import java.util.List;
import java.util.ArrayList;

public class Estudiante{
	private String id;
	private String nombre;
	private float promedio;
	
	public Estudiante(String id, String nombre, float promedio){
		this.id = id;
		this.nombre = nombre;
		this.promedio = promedio;
	}
	
	public String getId(){
		return id;
	}
	
	public String getNombre(){
		return nombre;
	}
	
	public float getPromedio(){
		return promedio;
	}
	
	public void setId(String id){
		this.id = id;
	}
	
	public void setNombre(String nombre){
		this.nombre = nombre;
	}
	
	public void setPromedio(float promedio){
		this.promedio = promedio;
	}
	
}