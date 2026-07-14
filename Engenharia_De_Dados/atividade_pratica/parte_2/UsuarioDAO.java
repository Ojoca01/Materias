import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoDatabase;

import org.bson.Document;

import java.util.Arrays;
import java.util.Date;

import static com.mongodb.client.model.Filters.eq;
import static com.mongodb.client.model.Updates.set;


public class UsuarioDAO {


    private final MongoCollection<Document> colecao;



    public UsuarioDAO() {


        MongoDatabase db =
                ConexaoMongo.conectar();


        colecao =
                db.getCollection("usuarios");


    }




    public void listarUsuarios() {


        boolean vazio = true;


        for (Document usuario : colecao.find()) {


            vazio = false;


            System.out.println(
                    "\nCPF: "
                    + usuario.getString("cpf")
            );


            System.out.println(
                    "Nome: "
                    + usuario.getString("nome")
            );


            System.out.println(
                    "Nascimento: "
                    + usuario.getString("dataNascimento")
            );


            System.out.println(
                    "Email: "
                    + usuario.getList(
                            "emails",
                            String.class
                    )
            );


            System.out.println(
                    "Telefone: "
                    + usuario.getList(
                            "telefones",
                            String.class
                    )
            );


            System.out.println(
                    "Login: "
                    + usuario.getString("login")
            );


            System.out.println("----------------------------");

        }



        if(vazio){

            System.out.println(
                    "Nenhum usuário encontrado."
            );

        }


    }





    public void inserirUsuario(


            String cpf,

            String nome,

            Date nascimento,

            String email,

            String telefone,

            String login,

            String senha


    ) {



        Document existente =
                colecao.find(
                        eq("cpf", cpf)
                ).first();



        if(existente != null){


            System.out.println(
                    "Erro: CPF já cadastrado."
            );


            return;

        }





        Document usuario =
                new Document();



        usuario.append(
                "cpf",
                cpf
        );


        usuario.append(
                "nome",
                nome
        );


        usuario.append(
                "dataNascimento",
                nascimento.toString()
        );


        usuario.append(
                "emails",
                Arrays.asList(email)
        );


        usuario.append(
                "telefones",
                Arrays.asList(telefone)
        );


        usuario.append(
                "login",
                login
        );


        usuario.append(
                "senha",
                senha
        );



        colecao.insertOne(usuario);



        System.out.println(
                "Usuário inserido com sucesso!"
        );


    }





    public void atualizarEmail(


            String cpf,

            String novoEmail


    ){



        var resultado =
                colecao.updateOne(


                        eq("cpf", cpf),


                        set(
                                "emails",
                                Arrays.asList(novoEmail)
                        )


                );



        if(resultado.getMatchedCount() > 0){


            System.out.println(
                    "Email atualizado com sucesso!"
            );


        }else{


            System.out.println(
                    "Usuário não encontrado."
            );


        }



    }






    public void removerUsuario(


            String cpf


    ){



        var resultado =
                colecao.deleteOne(
                        eq("cpf", cpf)
                );



        if(resultado.getDeletedCount() > 0){


            System.out.println(
                    "Usuário removido com sucesso!"
            );


        }else{


            System.out.println(
                    "Usuário não encontrado."
            );


        }



    }



}