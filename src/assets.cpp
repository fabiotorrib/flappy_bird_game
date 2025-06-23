/**
 * @file assets.cpp
 * @brief Carregamento e gerenciamento de assets gráficos/áudio.
 */

#include "../include/assets.hpp"

#include <memory>

// Assets globais
std::unique_ptr<Sound> selectSound;

/**
 * @brief Carrega recursos globais utilizados em múltiplas cenas.
 *
 * Atualmente apenas o efeito de som de seleção de menu é carregado, porém a
 * função pode ser estendida para outros assets compartilhados.
 */
void loadGlobalAssets() {
  selectSound = std::make_unique<Sound>("assets/selectSound.wav");
}

/**
 * @brief Libera os recursos globais previamente carregados.
 */
void unloadGlobalAssets() {
  selectSound.reset();
}

/**
 * @brief Constrói uma imagem fora da tela.
 * @param diretorio Caminho do arquivo de imagem.
 *
 * Define a posição inicial fora da área visível para evitar flickering até
 * que o programador defina coordenadas de desenho.
 * @throw std::bad_alloc Se @p diretorio não puder ser carregado.
 */
Image::Image(const char *diretorio) {
  image = al_load_bitmap(diretorio);
  if (!image) {
    std::cout << "ERRO: Falha ao carregar a imagem em: " << diretorio
              << std::endl;
    throw std::bad_alloc();
  }
  this->x = -1000;
  this->y = -1000;
}

/**
 * @brief Constrói uma imagem posicionada em coordenadas específicas.
 * @param diretorio Caminho do bitmap.
 * @param x Coordenada X.
 * @param y Coordenada Y.
 * @throw std::bad_alloc Se a imagem não puder ser carregada.
 */
Image::Image(const char *diretorio, float x, float y) {
  image = al_load_bitmap(diretorio);
  if (!image) {
    std::cout << "ERRO: Falha ao carregar a imagem em: " << diretorio
              << std::endl;
    throw std::bad_alloc();
  }
  this->x = x;
  this->y = y;
}

/**
 * @brief Desenha a imagem nas coordenadas especificadas.
 * @param x Posição X.
 * @param y Posição Y.
 */
void Image::Draw(float x, float y) {
  al_draw_bitmap(image, x, y, 0);
}

/**
 * @brief Desenha a imagem usando as coordenadas internas armazenadas.
 */
void Image::Draw() {
  al_draw_bitmap(image, x, y, 0);
}

/**
 * @brief Libera o bitmap associado.
 */
Image::~Image() {
  if (image) al_destroy_bitmap(image);
}

/**
 * @brief Constrói um objeto de música em loop.
 * @param diretorio Caminho do arquivo de áudio.
 * @throw std::bad_alloc Se falhar ao carregar o stream.
 */
Music::Music(const char *diretorio) {
  music = al_load_audio_stream(diretorio, 16, 8192);
  if (!music) {
    std::cout << "ERRO: Falha ao carregar a música em: " << diretorio
              << std::endl;
    throw std::bad_alloc();
  }
  al_set_audio_stream_playmode(music, ALLEGRO_PLAYMODE_LOOP);
}

/**
 * @brief Inicia a reprodução da música.
 */
void Music::playMusic() {
  al_attach_audio_stream_to_mixer(music, al_get_default_mixer());
}

/**
 * @brief Libera o stream de áudio.
 */
Music::~Music() {
  if (music) al_destroy_audio_stream(music);
}

/**
 * @brief Carrega um efeito sonoro.
 * @param diretorio Caminho do arquivo de som.
 * @throw std::bad_alloc Caso o sample não seja carregado.
 */
Sound::Sound(const char *diretorio) {
  sound = al_load_sample(diretorio);
  if (!sound) {
    std::cout << "ERRO: Falha ao carregar o som em: " << diretorio << std::endl;
    throw std::bad_alloc();
  }
}

/**
 * @brief Reproduz o efeito sonoro uma única vez.
 * @param volume Volume de 0.0 a 1.0.
 */
void Sound::playSound(float volume) {
  al_play_sample(sound, volume, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, nullptr);
}

/**
 * @brief Libera o sample de áudio.
 */
Sound::~Sound() {
  if (sound) al_destroy_sample(sound);
}

/**
 * @brief Carrega uma fonte bitmap.
 * @param diretorio Caminho para o arquivo de fonte.
 * @param size Tamanho em pontos.
 * @throw std::bad_alloc Se a fonte não puder ser carregada.
 */
TextFont::TextFont(const char *diretorio, int size) {
  font = al_load_font(diretorio, size, 0);
  if (!font) {
    std::cout << "ERRO: Falha ao carregar o som em: " << diretorio << std::endl;
    throw std::bad_alloc();
  }
}

/**
 * @brief Define a cor utilizada nos próximos desenhos de texto.
 */
void TextFont::setColor(int r, int g, int b) {
  this->r = r;
  this->g = g;
  this->b = b;
}

/**
 * @brief Desenha texto na tela.
 * @param texto Conteúdo a ser escrito.
 * @param alinhamento ALLEGRO_ALIGN_LEFT/CENTRE/RIGHT.
 * @param x Coordenada X.
 * @param y Coordenada Y.
 */
void TextFont::writeText(const char *texto, int alinhamento, float x, float y) {
  al_draw_text(font, al_map_rgb(r, g, b), x, y, alinhamento, texto);
}

/**
 * @brief Libera a fonte carregada.
 */
TextFont::~TextFont() {
  if (font) al_destroy_font(font);
}