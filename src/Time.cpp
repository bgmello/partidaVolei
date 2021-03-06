#include "Time.h"

#include <iomanip>

Time::Time(const Time& time) {
  for (const auto& jogador : time.jogadores) {
    this->jogadores.push_back(jogador->clone());
  }
  this->nomeTime = time.nomeTime;
  this->tipoJogadores = time.tipoJogadores;
}

Time ::Time(string nomeTime) {
  /** Construtor da classe time */

  this->nomeTime = nomeTime;
  jogadores.clear();
  tipoJogadores.clear();
}

bool Time ::isValid() {
  /** Verifica se o time está de acordo com as regras */

  if (tipoJogadores["levantador"] != 1 or tipoJogadores["libero"] != 1 or
      tipoJogadores["oposto"] != 1 or tipoJogadores["meia"] != 2 or
      tipoJogadores["ponta"] != 2)
    return false;
  return true;
}

int Time ::getHabilidadeTotal() {
  /** Retorna a habilidade total do time */

  if (!this->isValid()) {
    return -1;
  }
  int sumHab = 0;
  for (int i = 0; i < 7; ++i) sumHab += jogadores[i]->getHabilidade();
  return sumHab;
}

bool Time ::addJogador(string nome, string posicao, int vlrAtaque,
                       int vlrDefesa, int vlrPasse, int habilidadeAdi) {
  /** Adiciona um novo jogador ao time
   *
   * Argumentos:
   * string nome        ---> nome do jogador
   * string posicao     ---> posição do jogador
   * int vlrAtaque      ---> Valor de ataque desse jogador
   * int vlrDefesa      ---> Valor de defesa desse jogador
   * int vlrPasse       ---> Valor de passe desse jogador
   * int habilidadeAdi  ---> Habilidade adicional desse jogador de acordo com
   * sua posição
   *
   * Retorna:
   * True, caso o jogador seja adicionado ou a equipe já esteja completa e seja
   * válida False, caso a equipe esteja completa e seja inválida ou se a posição
   * do jogador não for encontrada
   */

  if ((int)jogadores.size() == 7) {
    if (this->isValid()) {
      return true;
    }
    return false;
  }

  for (int i = 0; i < (int)jogadores.size(); i++) {
    if (jogadores[i]->getNome() == nome) return false;
  }

  tipoJogadores[posicao]++;
  if (posicao == "levantador") {
    jogadores.push_back(unique_ptr<Jogador>(
        new Levantador(nome, vlrAtaque, vlrDefesa, vlrPasse, habilidadeAdi)));
    return true;
  }
  if (posicao == "libero") {
    jogadores.push_back(unique_ptr<Jogador>(
        new Libero(nome, vlrAtaque, vlrDefesa, vlrPasse, habilidadeAdi)));
    return true;
  }
  if (posicao == "meia") {
    jogadores.push_back(unique_ptr<Jogador>(
        new Meia(nome, vlrAtaque, vlrDefesa, vlrPasse, habilidadeAdi)));
    return true;
  }
  if (posicao == "ponta") {
    jogadores.push_back(unique_ptr<Jogador>(
        new Ponta(nome, vlrAtaque, vlrDefesa, vlrPasse, 0)));
    return true;
  }
  if (posicao == "oposto") {
    jogadores.push_back(unique_ptr<Jogador>(
        new Oposto(nome, vlrAtaque, vlrDefesa, vlrPasse, habilidadeAdi)));
    return true;
  }
  return false;
}

bool Time ::removeJogador(string nome) {
  /** Remove jogador do time
   *
   * Argumentos: string nome    ---> nome do jogador
   *
   * Retorna:
   * True, caso o jogador seja removido com sucesso
   * False, caso contrário
   */

  for (int i = 0; i < (int)jogadores.size(); ++i) {
    if (jogadores[i]->getNome() == nome) {
      tipoJogadores[jogadores[i]->getPosicao()]--;
      jogadores.erase(jogadores.begin() + i);
      return true;
    }
  }
  return false;
}

ostream& operator<<(ostream& o, const Time& time) {
  /** Printa as informações dos jogadores */

  if ((int)time.jogadores.size() == 0) {
    o << "Nao ha jogadores nesse time\n\n";
    return o;
  }

  int width = 20;

  o << "Os jogadores do time sao" << endl << endl;
  o << setw(width) << setfill(' ') << "Nome";
  o << setw(width) << setfill(' ') << "Posicao";
  o << setw(width) << setfill(' ') << "Valor ataque";
  o << setw(width) << setfill(' ') << "Valor defesa";
  o << setw(width) << setfill(' ') << "Valor passe";
  o << setw(width) << setfill(' ') << "Habilidade total" << endl;

  for (int i = 0; i < (int)time.jogadores.size(); ++i) {
    o << setw(width) << setfill(' ') << time.jogadores[i]->getNome();
    o << setw(width) << setfill(' ') << time.jogadores[i]->getPosicao();
    o << setw(width) << setfill(' ') << time.jogadores[i]->getvlrAtaque();
    o << setw(width) << setfill(' ') << time.jogadores[i]->getvlrDefesa();
    o << setw(width) << setfill(' ') << time.jogadores[i]->getvlrPasse();
    o << setw(width) << setfill(' ') << time.jogadores[i]->getHabilidade();
    o << endl;
  }
  return o;
}
