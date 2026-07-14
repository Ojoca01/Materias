import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoDatabase;
import org.bson.Document;
import static com.mongodb.client.model.Filters.eq;
import static com.mongodb.client.model.Updates.set;
public class CursoDAO {
    private final MongoCollection<Document> colecao;
    public CursoDAO(){
        MongoDatabase db =
                ConexaoMongo.conectar();
        colecao =
                db.getCollection("cursos");
    }
    private int proximoIdCurso(){
        int maior = 0;
        for(Document curso : colecao.find()){
            Integer id =
                    curso.getInteger("idCurso");
            if(id != null && id > maior){
                maior = id;
            }
        }
        return maior + 1;
    }
    public void listarCursos(){
        boolean vazio = true;
        for(Document curso : colecao.find()){
            vazio = false;
            System.out.println(
                    "\nID: "
                    + curso.getInteger("idCurso")
            );
            System.out.println(
                    "Nome: "
                    + curso.getString("nome")
            );
            System.out.println(
                    "Grau: "
                    + curso.getString("grau")
            );
            System.out.println(
                    "Turno: "
                    + curso.getString("turno")
            );
            System.out.println(
                    "Campus: "
                    + curso.getString("campus")
            );
            System.out.println(
                    "Nível: "
                    + curso.getString("nivel")
            );
            System.out.println(
                    "----------------------------"
            );
        }
        if(vazio){
            System.out.println(
                    "Nenhum curso cadastrado."
            );
        }
    }
    public void inserirCurso(
            String nome,
            String grau,
            String turno,
            String campus,
            String nivel
    ){
        Document existente =
                colecao.find(
                        eq("nome", nome)
                ).first();
        if(existente != null){
            System.out.println(
                    "Curso já cadastrado."
            );
            return;
        }
        Document curso =
                new Document()
                .append(
                        "idCurso",
                        proximoIdCurso()
                )
                .append(
                        "nome",
                        nome
                )
                .append(
                        "grau",
                        grau
                )
                .append(
                        "turno",
                        turno
                )
                .append(
                        "campus",
                        campus
                )
                .append(
                        "nivel",
                        nivel
                );
        colecao.insertOne(curso);
        System.out.println(
                "Curso inserido com sucesso!"
        );
    }
    public void atualizarCampus(
            int idCurso,
            String novoCampus
    ){
        var resultado =
                colecao.updateOne(
                        eq(
                                "idCurso",
                                idCurso
                        ),
                        set(
                                "campus",
                                novoCampus
                        )
                );
        if(resultado.getMatchedCount() > 0){
            System.out.println(
                    "Campus atualizado com sucesso!"
            );
        }else{

            System.out.println(
                    "Curso não encontrado."
            );
        }
    }
    public void removerCurso(
            int idCurso
    ){
        var resultado =
                colecao.deleteOne(
                        eq(
                                "idCurso",
                                idCurso
                        )
                );
        if(resultado.getDeletedCount() > 0){
            System.out.println(
                    "Curso removido com sucesso!"
            );
        }else{
            System.out.println(
                    "Curso não encontrado."
            );
        }
    }
}