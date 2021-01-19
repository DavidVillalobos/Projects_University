import java.util.List;
import java.util.ArrayList;

public class Curso{
	private String nombre;
	private String codigo;
	private int cupos;
	private List<Estudiante> estudiantes;
	
	public Curso(String nombre, String codigo, int cupos){
		this.nombre = nombre;
		this.codigo = codigo;
		this.estudiantes = new ArrayList<Estudiante>();
		this.cupos = cupos;
	}
	
	public String getNombre(){
		return nombre;
	}
	
	public String getCodigo(){
		return codigo;
	}
	
	public int getCupos(){
		return cupos;
	}
	
	public List<Estudiante> getEstudiantes(){
		return estudiantes;
	}
	
	public void setNombre(String nombre){
		this.nombre = nombre;
	}
	
	public void setCodigo(String codigo){
		this.codigo = codigo;
	}
	
	public void setCupos(int cupos){
		this.cupos = cupos;
	}
	
	public void setEstudiantes(	List<Estudiante> estudiantes){
		this.estudiantes = estudiantes;
	}
	
}