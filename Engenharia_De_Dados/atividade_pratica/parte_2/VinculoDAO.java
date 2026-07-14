import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoDatabase;
import org.bson.Document;
import java.util.ArrayList;
import java.util.List;
import static com.mongodb.client.model.Filters.eq;
public class VinculoDAO {
    private final MongoCollection<Document> usuarios;
    private final MongoCollection<Document> cursos;
    public VinculoDAO(){
        MongoDatabase db =
                ConexaoMongo.conectar();
        usuarios =
                db.getCollection("usuarios");
        cursos =
                db.getCollection("cursos");
    }
    private int proximoIdVinculo(){
        int maior = 0;
        for(Document usuario : usuarios.find()){
            Document estudante =
                    usuario.get(
                            "estudantes",
                            Document.class
                    );
            if(estudante == null)
                continue;
            List<Document> vinculos =
                    estudante.getList(
                            "vinculos",
                            Document.class
                    );
            if(vinculos == null)
                continue;
            for(Document vinculo : vinculos){
                Integer id =
                        vinculo.getInteger(
                                "idVinculo"
                        );
                if(id != null && id > maior){
                    maior = id;
                }
            }
        }
        return maior + 1;
    }
    public void listarVinculos(){
        boolean encontrado = false;
        for(Document usuario : usuarios.find()){
            Document estudante =
                    usuario.get(
                            "estudante",
                            Document.class
                    );
            if(estudante == null)
                continue;
            List<Document> vinculos =
                    estudante.getList(
                            "vinculos",
                            Document.class
                    );
            if(vinculos == null)
                continue;
            for(Document vinculo : vinculos){
                encontrado = true;
                System.out.println(
                        "\nID Vínculo: "
                        + vinculo.getInteger(
                                "idVinculo"
                        )
                );
                System.out.println(
                        "Matrícula: "
                        + estudante.getString(
                                "matricula"
                        )
                );
                System.out.println(
                        "Curso: "
                        + vinculo.getInteger(
                                "idCurso"
                        )
                );
                System.out.println(
                        "Status: "
                        + vinculo.getString(
                                "status"
                        )
                );
                System.out.println(
                        "----------------------------"
                );
            }
        }
        if(!encontrado){
            System.out.println(
                    "Nenhum vínculo encontrado."
            );
        }
    }
    public void inserirVinculo(
            String matricula,
            int idCurso,
            String status
    ){
        Document curso =
                cursos.find(
                        eq(
                                "idCurso",
                                idCurso
                        )
                ).first();
        if(curso == null){
            System.out.println(
                    "Curso não encontrado."
            );
            return;
        }
        Document usuario =
                usuarios.find(
                        eq(
                                "estudante.matricula",
                                matricula
                        )
                ).first();
        if(usuario == null){
            System.out.println(
                    "Estudante não encontrado."
            );
            return;
        }
        Document estudante =
                usuario.get(
                        "estudante",
                        Document.class
                );
        List<Document> vinculos =
                estudante.getList(
                        "vinculos",
                        Document.class
                );
        if(vinculos == null){
            vinculos =
                    new ArrayList<>();
        }
        Document novoVinculo =
                new Document()
                .append(
                        "idVinculo",
                        proximoIdVinculo()
                )
                .append(
                        "idCurso",
                        idCurso
                )
                .append(
                        "status",
                        status
                );
        vinculos.add(novoVinculo);
        estudante.put(
                "vinculos",
                vinculos
        );
        usuarios.replaceOne(
                eq(
                        "cpf",
                        usuario.getString(
                                "cpf"
                        )
                ),
                usuario
        );
        System.out.println(
                "Vínculo inserido com sucesso!"
        );
    }
    public void atualizarStatus(
            int idVinculo,
            String novoStatus
    ){
        for(Document usuario : usuarios.find()){
            Document estudante =
                    usuario.get(
                            "estudante",
                            Document.class
                    );
            if(estudante == null)
                continue;
            List<Document> vinculos =
                    estudante.getList(
                            "vinculos",
                            Document.class
                    );
            if(vinculos == null)
                continue;
            for(Document vinculo : vinculos){
                Integer id =
                        vinculo.getInteger(
                                "idVinculo"
                        );
                if(id != null &&
                        id.equals(idVinculo)){
                    vinculo.put(
                            "status",
                            novoStatus
                    );
                    usuarios.replaceOne(
                            eq(
                                    "cpf",
                                    usuario.getString(
                                            "cpf"
                                    )
                            ),
                            usuario
                    );
                    System.out.println(
                            "Status atualizado com sucesso!"
                    );
                    return;
                }
            }
        }
        System.out.println(
                "Vínculo não encontrado."
        );
    }
    public void removerVinculo(
            int idVinculo
    ){
        for(Document usuario : usuarios.find()){
            Document estudante =
                    usuario.get(
                            "estudante",
                            Document.class
                    );
            if(estudante == null)
                continue;
            List<Document> vinculos =
                    estudante.getList(
                            "vinculos",
                            Document.class
                    );
            if(vinculos == null)
                continue;
            for(int i = 0; i < vinculos.size(); i++){
                Integer id =
                        vinculos.get(i)
                                .getInteger(
                                        "idVinculo"
                                );
                if(id != null &&
                        id.equals(idVinculo)){
                    vinculos.remove(i);
                    estudante.put(
                            "vinculos",
                            vinculos
                    );
                    usuarios.replaceOne(
                            eq(
                                    "cpf",
                                    usuario.getString(
                                            "cpf"
                                    )
                            ),
                            usuario
                    );
                    System.out.println(
                            "Vínculo removido com sucesso!"
                    );
                    return;
                }
            }
        }
        System.out.println(
                "Vínculo não encontrado."
        );
    }
}