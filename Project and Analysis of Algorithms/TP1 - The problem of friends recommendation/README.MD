# TP1 - The problem of friends recommendation

Recomendação de novos amigos é um problema comum em redes sociais, pois permite aos usuários expandirem as suas relações de amizade na rede e também a aumentarem as suas interações. Neste trabalho as amizades dos usuários de uma rede social são representadas por um grafo não direcionado, onde os vértices são os usuários e as arestas indicam se há uma relação de amizade entre eles. 

O objetivo deste trabalho é (1) determinar se todos os usuários da rede social estão conectados, seja através de uma conexão direta ou indiretamente através de outros amigos, e (2) calcular um subgrafo de conexões cuja função de qualidade $r$ seja máxima. Esta função de qualidade representa a configuração de amizade ideal para a rede social e é dada por 

 	r = \frac{\sum_{i=1}^{E} Friendship_i}{\sum_{i=1}^{E} Distance_i}, \forall i \in E

onde *Friendship* e *Distance* são métricas que quantificam as relações de amizades dos usuários e indicam, respectivamente, o nível de amizade entre dois usuários e uma suposta distância física entre eles.
