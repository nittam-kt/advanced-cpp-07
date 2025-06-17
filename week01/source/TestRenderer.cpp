#pragma once

#include "TestRenderer.h"
#include "D3DManager.h"

using namespace DirectX;
using namespace UniDx;


void TestRenderer::Render(const UniDx::Camera& camera)
{
    // ���݂�Transform�ƃJ�����̏����V�F�[�_�[��ConstantBuffer�ɓ]��
    Renderer::UpdatePositionCameraCBuffer(camera);

    UniDx::Debug::Log(L"Render");

    // �`�揈��
    // �O�p�`�̕`��
    {
        // �P���_�̌`��(����͍��W����)
        struct VertexType
        {
            Vector3 Pos;	// ���W
        };
        // �O�p�`����邽�߁A���_���R���
        VertexType v[4] = {
            {{-0.5,-0.5,0}},
            {{-0.5,0.5,0}},
            {{0.5,-0.5,0}},
            {{0.5,0.5,0}},
        };
        //-----------------------------
        // ���_�o�b�t�@�쐬
        // �E�r�f�I���������Ɂu���_�o�b�t�@�v�Ƃ����`�ō��K�v������
        // �E����͕`��̂��тɍ��
        //-----------------------------
        // �쐬����o�b�t�@�̎d�l�����߂�
        D3D11_BUFFER_DESC vbDesc = {};
        vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// �f�o�C�X�Ƀo�C���h����Ƃ��̎��(���_�o�b�t�@�A�C���f�b�N�X�o�b�t�@�A�萔�o�b�t�@�Ȃ�)
        vbDesc.ByteWidth = sizeof(v);					// �쐬����o�b�t�@�̃o�C�g�T�C�Y
        vbDesc.MiscFlags = 0;							// ���̑��̃t���O
        vbDesc.StructureByteStride = 0;					// �\�����o�b�t�@�̏ꍇ�A���̍\���̂̃T�C�Y
        vbDesc.Usage = D3D11_USAGE_DEFAULT;				// �쐬����o�b�t�@�̎g�p�@
        vbDesc.CPUAccessFlags = 0;

        // ��̎d�l��n���Ē��_�o�b�t�@������Ă��炤
        ComPtr<ID3D11Buffer> vb;
        D3D11_SUBRESOURCE_DATA initData = { &v[0], sizeof(v), 0 };	// �������ރf�[�^

        // ���_�o�b�t�@�̍쐬
        D3DManager::instance->GetDevice()->CreateBuffer(&vbDesc, &initData, &vb);

        //++++++++++++++++++++ ��������`�悵�Ă����܂� ++++++++++++++++++++

        // ���_�o�b�t�@��`��Ŏg����悤�ɃZ�b�g����
        UINT stride = sizeof(VertexType);
        UINT offset = 0;
        D3DManager::instance->GetContext()->IASetVertexBuffers(0, 1, vb.GetAddressOf(), &stride, &offset);

        // �v���~�e�B�u�E�g�|���W�[���Z�b�g
        D3DManager::instance->GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

        UniDx::Debug::Log(__LINE__);
        //-----------------------------
        // �V�F�[�_�[���Z�b�g
        //-----------------------------
        SetShaderForRender();

        //-----------------------------
        // �`����s
        //-----------------------------
        // �f�o�C�X�R���e�L�X�g�A��L�̃Z�b�g�������e�ŕ`�悵�Ă��������A�Ƃ��肢����
        D3DManager::instance->GetContext()->Draw(4, 0);
        UniDx::Debug::Log(__LINE__);
    }
}


void TestRenderer::OnEnable()
{
    Renderer::OnEnable();
    materials.push_back(Material());
    materials.back().initialize(L"../UniDx/SimplePositionShader.hlsl");
}