#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class UI
{
public:

    UI()
    {
        main_viewport = ImGui::GetMainViewport();
    }

    void renderFrame(Scene &scene, Framebuffer &framebuffer, int width, 
                        int height, int window_width, int window_height,
                        MainWindow &window)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x, main_viewport->WorkPos.y));
        ImGui::SetNextWindowSize(main_viewport->Size);
        bool p_open = true;
        ImGui::Begin("Main", &p_open, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_MenuBar);
        {   
            if (ImGui::BeginMenuBar())
            {
                if (ImGui::BeginMenu("File"))
                {
                    ImGui::EndMenu();
                }
                ImGui::EndMenuBar();
            }
    
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
            if (ImGui::BeginTable("split", 1, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable, ImVec2((float) window_width / 3, 0)))
            {
                for (int obj_i = 0; obj_i < scene.objects.size(); obj_i++)
                {
                    showObject("Object", obj_i, scene.objects[obj_i]);
                }
                ImGui::EndTable();
            }
            ImGui::PopStyleVar();
            ImGui::SameLine();
            ImGui::BeginChild("Hello, world!", ImVec2(0, 0), true);                          // Create a window called "Hello, world!" and append into it.
            ImGui::Image(reinterpret_cast<ImTextureID>(framebuffer.getColorTexture()), 
                         ImVec2(width, height), ImVec2(0,1), ImVec2(1,0));

            if (ImGui::IsWindowFocused())
            {
                window.disableCursor();
                //inputHandler.activeInput = true;
                window.setInputActive();
            }
            ImGui::EndChild();
        }

        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

private:

    void showObject(const char* name, int uid, Object &object)
    {
        ImGui::PushID(uid);

        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::AlignTextToFramePadding();

        bool node_open = ImGui::TreeNode("Object", "%s_%u", object.name.c_str(), uid);
        
        if (node_open)
        {
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::AlignTextToFramePadding();

            ImGui::InputFloat3("Position", object.position_arr);
            ImGui::InputFloat3("Scale", object.scale_arr);

            ImGui::TreePop();
        }
        ImGui::PopID();
    }

    ImGuiViewport* main_viewport;
};