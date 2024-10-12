#include "caixa_de_texto.hpp"
#include "src/ui/painel/painel.hpp"
#include <exprtk.hpp>
#include <iostream>
#include <sstream>
#include <iomanip>

std::string to_short_string(double value)
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(6) << value;  // Define 6 casas decimais no máximo

    std::string result = oss.str();

    // Remover zeros desnecessários após a vírgula
    result.erase(result.find_last_not_of('0') + 1, std::string::npos);
    if (result.back() == '.') {
        result.pop_back();  // Remove o ponto final se ele for o último caractere
    }

    return result;
}

BubbleUI::Widgets::CaixaTexto::CaixaTexto(const std::string &mensagem)
    : gatilho1(false), gatilho2(false), mensagem(mensagem)
{
    letra_padding = { 5, 5 };
    resolucao = 12;
    lines_box_limite = 3;
    configurar();
    moldura.defCor({ 0.05f, 0.05f, 0.05f });
}

BubbleUI::Widgets::CaixaTexto::CaixaTexto(std::shared_ptr<std::string> buffer, const std::string& mensagem)
    : mensagem(mensagem), buffer_texto(buffer) 
{
    if (buffer) {
        texto = buffer->c_str(); texto_cursor_index = buffer->size() - 1;
    }
    letra_padding = { 5, 5 };
    resolucao = 12;
    lines_box_limite = 3;
    configurar();
    moldura.defCor({ 0.05f, 0.05f, 0.05f });
}

BubbleUI::Widgets::CaixaTexto::CaixaTexto(std::string* buffer, const std::string& mensagem, const bool &apenas_numeros)
    : mensagem(mensagem), buffer_texto(buffer), apenasNumeros(apenas_numeros)
{
    if (buffer) {
        texto = buffer->c_str(); texto_cursor_index = buffer->size() - 1;
    }
    letra_padding = { 5, 5 };
    resolucao = 12;
    lines_box_limite = 3;
    configurar();
    moldura.defCor({ 0.05f, 0.05f, 0.05f });
}

void BubbleUI::Widgets::CaixaTexto::atualizar()
{
    Texto::atualizar(); // Atualiza texto

    if (painel->selecionado) 
    {
        if (colisao.mouseEmCima()) {
            contexto->cursor = contexto->cursor_texto;
            if (inputs->mouseEnter == GLFW_PRESS)iniciarSelecao();
            else selecionando_texto = false;
        } // atualiza Cursor
        if (selecionado) atualizarInputs(); // Atualiza entrada
        if (selecionando_texto) area_de_selecao = { static_cast<float>(mouse_pos_ini.x), static_cast<float>(mouse_pos_ini.y), (int)inputs->mousex, (int)inputs->mousey };
    }

    //for (auto& letra : letras_rect) // Desenha cursor do texto
    //{
    //    if (letra.index == texto_cursor_index) texto_cursor_pos = letra.rect; texto_cursor_pos.w = 1;
    //}
    // Atribui texto da frase para o buffer
    if (buffer_texto.get())
    {
        buffer_texto->clear();
        for (size_t i = 0; i < texto.size(); i++)   buffer_texto->push_back(texto[i]);
    }

    // Defini mensagem caso texto vazio
    if (texto.empty())
    {
        frase = mensagem;
        cor = { 0.7f, 0.7f, 0.7f};
    }
    else
    {
        frase = texto;
        cor = { 1.f, 1.f, 1.f };
    }

    // Redimensiona moldura e colisao
    colisao.defRect({box_pos.x, box_pos.y, (int)box_size.x, (int)box_size.y});
    moldura.defTam({ static_cast<int>(box_size.x), static_cast<int>(box_size.y) }); moldura.defPos({ static_cast<int>(box_pos.x), static_cast<int>(box_pos.y) });
    moldura.atualizar();

    painel->posicaoWidget.y += painel->widgetPadding.y;
}

void BubbleUI::Widgets::CaixaTexto::renderizar() const
{
    moldura.renderizar();
    Texto::renderizar();
    // Renderiza o cursor
    //if (Bubble::Tempo::s_passados % 2 == 0)
    //{
    //    shaderQuad.use();
    //    shaderQuad.setCor("quadrado.cor", { 1, 1, 1, 0.95f });
    //    shaderQuad.setVec2("quadrado.posicao", texto_cursor_pos.x, texto_cursor_pos.y);
    //    shaderQuad.setVec2("quadrado.tamanho", texto_cursor_pos.z, texto_cursor_pos.w);
    //
    //    glBindVertexArray(rect_vertex.VAO);
    //    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(rect_vertex.indices.size()), GL_UNSIGNED_INT, 0);
    //    glBindVertexArray(0);
    //}
}

void BubbleUI::Widgets::CaixaTexto::defPainel(Painel* painel)
{
    BubbleUI::Widgets::Texto::defPainel(painel);
    contexto = painel->obterContexto();
    inputs = painel->obterContexto()->inputs; // Simplifica o acesso
}

static std::string resolverExpressao(const std::string& expression_string) {
    typedef exprtk::symbol_table<double> symbol_table_t;
    typedef exprtk::expression<double>   expression_t;
    typedef exprtk::parser<double>       parser_t;

    symbol_table_t symbol_table;
    expression_t expression;
    expression.register_symbol_table(symbol_table);

    parser_t parser;
    if (!parser.compile(expression_string, expression)) {
        std::cerr << "Erro ao compilar a expressão: " << expression_string << std::endl;
        return "ERRO";
    }

    double result = expression.value();
    std::cout << "Resultado: " << result << std::endl;

    return to_short_string(result);
}

void BubbleUI::Widgets::CaixaTexto::processarEntrada(char c)
{
    texto_cursor_index = texto.size();
    if (c == '\b' && texto_cursor_index > 0) // Backspace
    {
        texto.erase(texto_cursor_index - 1, 1); // Remove o caractere antes do cursor
        return;
    }
    else if (!apenasNumeros && c != '\b') // Entrada de texto normal
    {
        texto.insert(texto_cursor_index, 1, c); // Insere o caractere na posição do cursor
    }
    else if (apenasNumeros && (std::isdigit(c) || c == '-'|| c == '+'|| c == '*'|| c == '/'|| c == '('|| c == ')'|| c == '.')) // Entrada apenas de números
    {
        texto.insert(texto_cursor_index, 1, c); // Insere apenas números
    }
    else if (apenasNumeros && inputs->isKeyPressed(ENTER))
    {
        if(resolverExpressao(texto) != "ERRO")
            texto = resolverExpressao(texto);
    }
}


double tempo_inicial = 0.0;

void BubbleUI::Widgets::CaixaTexto::atualizarInputs()
{
    double tempo_atual = glfwGetTime(); // Obtenha o tempo atual
    if (gatilho1) {
        cronometro = tempo_atual - tempo_inicial;
    }

    if (inputs->isKeyPressed(BS) && !texto.empty() && !gatilho1) // Backspace
    {
        inputs->char_press = true;
        inputs->letra = '\b';
    }
    if (inputs->isKeyPressed(ENTER) && !gatilho1) // Enter
    {
        inputs->char_press = true;
        inputs->letra = '\n';
    }
    if (inputs->char_press && !gatilho1) // Detecta primeiro toque
    {
        gatilho1 = true;
        inputs->char_press = false;
        processarEntrada(inputs->letra);
        cronometro = 0.0f;
        tempo_inicial = glfwGetTime(); // Armazene o tempo inicial
    }

    if (cronometro >= 0.4f) // Ativa repetição após o tempo inicial de 0.4 segundos
    {
        gatilho2 = true;
    }

    if (inputs->teclado_action == GLFW_RELEASE)
    {
        gatilho2 = false;
        gatilho1 = false;
        tempo_inicial = 0.0f;
    }

    // Processa repetição com intervalo de 0.05 segundos
    if (gatilho1 && gatilho2)
    {
        if (cronometro >= 0.05f) // 5 centésimos de segundos
        {
            processarEntrada(inputs->letra);
            cronometro = 0.0f;
            tempo_inicial = glfwGetTime(); // Reinicie o tempo inicial
        }
    }
}

void BubbleUI::Widgets::CaixaTexto::iniciarSelecao()
{
    if (!selecionando_texto) { selecionado = false; mouse_pos_ini = { (int)inputs->mousex, (int)inputs->mousey }; selecionando_texto = true; }
    else selecionado = true;
}