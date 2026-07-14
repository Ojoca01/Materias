import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoDatabase;
import org.bson.Document;
import java.util.ArrayList;
import static com.mongodb.client.model.Filters.eq;
import static com.mongodb.client.model.Updates.set;
import static com.mongodb.client.model.Updates.unset;
public class EstudanteDAO {
    private final MongoCollection<Document> colecao;
    public EstudanteDAO(){
        MongoDatabase db =
                ConexaoMongo.conectar();
        colecao =
                db.getCollection("usuarios");
    }
    public void listarEstudantes(){
        boolean encontrado = false;
        for(Document usuario : colecao.find()){
            Document estudante =
                    usuario.get(
                            "estudantes",
                            Document.class
                    );
            if(estudante != null){
                encontrado = true;
                System.out.println(
                        "\nMatrícula: "
                        + estudante.getString("matricula")
                );
                System.out.println(
                        "CPF: "
                        + usuario.getString("cpf")
                );
                System.out.println(
                        "MC: "
                        + estudante.getDouble("mc")
                );
                System.out.println(
                        "Ano ingresso: "
                        + estudante.getInteger(
                                "anoIngresso"
                        )
                );
                System.out.println(
                        "----------------------------"
                );
            }
        }
        if(!encontrado){
            System.out.println(
                    "Nenhum estudante encontrado."
            );
        }
    }
    public void inserirEstudante(
            String matricula,

            String cpf,

            double mc,

            int anoIngresso
    ){
        Document usuario =
                colecao.find(
                        eq("cpf", cpf)
                ).first();
        if(usuario == null){
            System.out.println(
                    "Usuário não encontrado."
            );
            return;
        }
        Document estudanteExistente =

                usuario.get(
                        "estudante",
                        Document.class
                );
        if(estudanteExistente != null){
            System.out.println(
                    "Usuário já possui estudante cadastrado."
            );
            return;
        }
        Document estudante = new Document().append(
                        "matricula",
                        matricula
                )
                .append(
                        "mc",
                        mc
                )
                .append(
                        "anoIngresso",
                        anoIngresso
                )
                .append(
                        "vinculos",
                        new ArrayList<Document>()
                );
        colecao.updateOne(
                eq("cpf", cpf),
                set(
                        "estudante",
                        estudante
                )
        );
        System.out.println(
                "Estudante inserido com sucesso!"
        );
    }
    public void atualizarMC(
            String matricula,
            double novoMC
    ){
             var resultado =
                colecao.updateOne(
                        eq(
                                "estudante.matricula",
                                matricula
                        ),
                        set(
                                "estudante.mc",
                                novoMC
                        )
                );
        if(resultado.getMatchedCount() > 0){
     System.out.println(
                    "MC atualizado com sucesso!"
            );
        }else{
            System.out.println(
                    "Estudante não encontrado."
            );
        }
    }
    public void removerEstudante(
            String matricula
    ){
        var resultado =
                colecao.updateOne(
                        eq(
                                "estudante.matricula",
                                matricula
                        ),
                      unset(
                                "estudante"
                        )
                );
       if(resultado.getMatchedCount() > 0){
          System.out.println(
                    "Estudante removido com sucesso!"
            );
        }else{
            System.out.println(
                    "Estudante não encontrado."
            );
        }
    }
}