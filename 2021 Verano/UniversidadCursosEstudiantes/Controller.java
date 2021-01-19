import java.util.List;
import java.util.ArrayList;

public class Controller{
	
	private Model model;
	private View view;
	
	public Controller(){
		this.model = new Model();
		this.view = new View();
	}
	
	public Model getModel(){
		return model;
	}
	
	public void setModel(Model model){
		this.model = model;
	}

	public View getView(){
		return view;
	}
	
	public void setView(View view){
		this.view = view;
	}
	
	public void iniciar(){
		model.getUniversidad().setEstudiantes(FileManager.recuperarEstudiantes());
		model.getUniversidad().setCursos(FileManager.recuperarCursos());
		while (true) {
			View.clearScreen();
			View.print("Bienvenido - Universidad - " + model.getUniversidad().getNombre() + '\n');
			View.print("1] Visualizar Cursos\n");
			View.print("2] Visualizar Estudiantes\n");
			View.print("3] Visualizar Cursos y Estudiantes\n");
			View.print("4] Agregar nuevo curso\n");
			View.print("5] Agregar nuevo estudiante\n");
			View.print("6] Matricular estudiante en curso\n");
			View.print("7] Eliminar curso\n");
			View.print("8] Eliminar estudiante\n");
			View.print("9] Salir\n");
			View.print("Digite un numero: ");
			int opcion = View.getInt();
			View.clearScreen();
			switch (opcion)
			{
			case 1: {
				View.print("Visualizar Cursos\n");
				View.print(model.getUniversidad().getCursos().toString());
				View.pause();
				break;
			}
			case 2: {
				View.print("Visualizar Estudiantes\n");
				View.print(model.getUniversidad().getEstudiantes().toString());
				View.pause();
				break;
			}
			case 3: {
				View.print("Visualizar Cursos y Estudiantes\n");
				 // View.print(model.getUniversidad().getCursos().toStringCursosEstudiantes());
				View.pause();
				break;
			}
			case 4: {
				View.print("Agregar Curso\n");
				View.print("Digite los datos del curso\n");
				View.print("Codigo: ");
				String codigo = View.getString();
				View.print("Nombre: ");
				String nombre = View.getString();
				View.print("Cupos: ");
				int cupos = View.getInt();
				model.getUniversidad().getCursos().add(new Curso(codigo, nombre, cupos));
				View.print("El curso se ha agregado correctamente\n");
				View.pause();
				break;
			}
			case 5: {
				View.print("Agregar Estudiante\n");
				View.print("Digite los datos del estudiante\n");
				View.print("Id: ");
				String id = View.getString();
				View.print("Nombre: ");
				String nombre = View.getString();
				View.print("Promedio: ");
				float promedio = View.getFloat();
				model.getUniversidad().getEstudiantes().add(new Estudiante(id, nombre, promedio));
				View.print("El estudiante se ha agregado correctamente\n");
				View.pause();
				break;
			}
			case 6: {
				View.print("Matricular Estudiante en Curso\n");
				View.print("Digite el Id del estudiante: ");
				String id_estudiante = View.getString();
				Estudiante aux = buscarEstudiante(id_estudiante);
				if(aux != null){
					View.print("Digite el Id del curso: ");
					String id_curso = View.getString();
					Curso aux2 = buscarCurso(id_curso);
					if(aux2 != null){
						if(aux2.getEstudiantes().add(aux)){
							View.print("El estudiante se ha matriculado correctamente\n");
						}else{
							View.print("Ya no hay cupo para el curso " + id_curso + "\n");
						}
					}else{
						View.print("No se encontro un curso con el codigo " + id_curso + "\n");
					}				
				}else{
					View.print("No se encontro un estudiante con el id " + id_estudiante + "\n");
				}
		
				View.pause();
				break;
			}
			case 7: { 
				View.print("Eliminar Curso\n");
				View.print("Digite el codigo del curso a eliminar: ");
				String codigo = View.getString();
				if (model.getUniversidad().getCursos().remove(buscarIndiceCurso(codigo)) != null) {
					View.print("El curso con el codigo " + codigo + " ha sido eliminado correctamente\n");
				}
				else {
					View.print("No se encontro un curso con el codigo " + codigo + "\n");
				}
				View.pause();
				break;
			}
			case 8: { 
				View.print("Eliminar estudiante\n");
				View.print("Digite el id del estudiante a eliminar: ");
				String id = View.getString();
				if (model.getUniversidad().getEstudiantes().remove(buscarIndiceEstudiante(id)) != null) {
					View.print("El estudiante con el id " + id + " ha sido eliminado correctamente\n");
				}
				else {
					View.print("No se encontro un estudiante con el id " + id + "\n");
				}
				View.pause();
				break;
			}
			case 9: { 
				// Guardar cursos
				FileManager.guardarEstudiantes(model.getUniversidad().getEstudiantes());
				FileManager.guardarCursos(model.getUniversidad().getCursos());
				return; 
			}
			default: {
				View.print("Usted a digitado una opcion que no se encuentra en el menu\n");
				View.pause();
				break;
			}
			}
		}
	}

	public Estudiante buscarEstudiante(String id) {
    	for (Estudiante e : model.getUniversidad().getEstudiantes()) {
        	if (e.getId().equals(id)) {
            	return e;
        	}
    	}
    	return null;
	}

	public int buscarIndiceEstudiante(String id) {
		int i = 0;
		for (Estudiante e : model.getUniversidad().getEstudiantes()) {
        	if (e.getId().equals(id)) {
            	return i;
			}
			i++;
    	}
    	return -1;
	}

	public Curso buscarCurso(String codigo) {
    	for (Curso c : model.getUniversidad().getCursos()) {
        	if (c.getCodigo().equals(codigo)) {
            	return c;
        	}
    	}
    	return null;
	}

	public int buscarIndiceCurso(String codigo) {
		int i = 0;
		for (Curso c : model.getUniversidad().getCursos()) {
        	if (c.getCodigo().equals(codigo)) {
            	return i;
			}
			i++;
    	}
    	return -1;
	}
}