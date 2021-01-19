import java.util.Scanner;
import java.io.*;
import java.util.List;
import java.util.ArrayList;

public class FileManager{
	
	private static String PATH_PROJECT = "C://Users//luisd//Desktop//UniversidadCursosEstudiantes";
	private static String FILE_STUDENTS = PATH_PROJECT + "//estudiantes.txt";
	private static String FILE_CURSES = PATH_PROJECT +  "//cursos.txt";
	
	public FileManager(){ }
	
	public static void guardarCursos(List<Curso> cursos){
		FileWriter fichero = null;
        PrintWriter pw = null;
        try
        {
            fichero = new FileWriter(FILE_CURSES);
            pw = new PrintWriter(fichero);
			for(Curso c : cursos){
				pw.println(c.getNombre() + "/" + c.getCodigo() + "/" + c.getCupos());
			}
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
           try {
           if (null != fichero)
              fichero.close();
           } catch (Exception e2) {
              e2.printStackTrace();
           }
        }
	}
	
	public static void guardarEstudiantes(List<Estudiante> estudiantes){
		FileWriter fichero = null;
        PrintWriter pw = null;
        try
        {
            fichero = new FileWriter(FILE_STUDENTS);
            pw = new PrintWriter(fichero);
			for(Estudiante e : estudiantes){
				pw.println(e.getId() + "/" + e.getNombre() + "/" + e.getPromedio());
			}
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
           try {
           if (null != fichero)
              fichero.close();
           } catch (Exception e2) {
              e2.printStackTrace();
           }
        }
	}
	
	public static List<Curso> recuperarCursos(){
		List<Curso> c = new ArrayList<Curso>();
		File archivo = null;
		FileReader fr = null;
		BufferedReader br = null;
		try {
			archivo = new File(FILE_CURSES);
			fr = new FileReader(archivo);
			br = new BufferedReader(fr);
			String linea;
			while( ( linea = br.readLine() ) != null ){
				String[] curse = linea.split("/", 3); 
				c.add(new Curso(curse[0], curse[1],  Integer.valueOf(curse[2])));
			}
		}catch(Exception e1){
			e1.printStackTrace();
		}finally{
			try{                    
				if( null != fr ){   
					fr.close();     
				}                  
			}catch (Exception e2){ 
				e2.printStackTrace();
			}
		}
		return c;
	}
	
	public static List<Estudiante> recuperarEstudiantes(){
		List<Estudiante> e = new ArrayList<Estudiante>();
		File archivo = null;
		FileReader fr = null;
		BufferedReader br = null;
		try {
			archivo = new File(FILE_STUDENTS);
			fr = new FileReader(archivo);
			br = new BufferedReader(fr);
			String linea;
			while( ( linea = br.readLine() ) != null ){
				String[] student = linea.split("/", 3); 
				e.add(new Estudiante(student[0], student[1], Float.parseFloat(student[2])));
			}
		}catch(Exception e1){
			e1.printStackTrace();
		}finally{
			try{                    
				if( null != fr ){   
					fr.close();     
				}                  
			}catch (Exception e2){ 
				e2.printStackTrace();
			}
		}
		return e;
	}
}