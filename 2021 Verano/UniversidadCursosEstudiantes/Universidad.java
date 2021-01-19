import java.util.List;
import java.util.ArrayList;

public class Universidad{
	private String nombre;
	private List<Estudiante> estudiantes;
	private List<Curso> cursos;
	
	public Universidad(String nombre){
		this.nombre = nombre;
		this.estudiantes = new ArrayList<Estudiante>(); 
		this.cursos = new ArrayList<Curso>();
	}
	
	public String getNombre(){
		return nombre;
	}
	
	public List<Estudiante> getEstudiantes(){
		return estudiantes;
	}
	
	public List<Curso> getCursos(){
		return cursos;
	}
	
	public void setNombre(String nombre){
		this.nombre = nombre;
	}
	
	public void setEstudiantes(List<Estudiante> estudiantes){
		this.estudiantes = estudiantes;
	}
	
	public void setCursos(List<Curso> cursos){
		this.cursos = cursos;
	}
	
}