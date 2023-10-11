#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <malloc.h>
#include <windows.h>

typedef struct {
    char hoTen[30];
    int tuoi;
    float diemTB;
} Data;
typedef struct Node{
    Data data;
    struct Node* next;
}Node;
typedef struct {
    Node* pHead;
    Node* pTail;
}List;
void init(List* l){
    l->pHead=NULL;
    l->pTail=NULL;
}
Data nhapData(){
    Data sv;
    printf("Nhap ho va ten: ");
    fflush(stdin);
    gets(sv.hoTen);
    printf("Nhap tuoi: ");
    scanf("%d",&sv.tuoi);
    printf("Nhap diem trung binh: ");
    scanf("%f",&sv.diemTB);
    return sv;
}
Node* taoNode(Data data){
    Node* pNode= (Node*)malloc(sizeof(Node));
    pNode->next=NULL;
    pNode->data=data;
    return pNode;
}
void themVaoDau(List* l, Node* pNode){
    if (pNode==NULL) {printf("Thong tin khong the khoi tao.\n");return;}
    if (l->pHead==NULL){
        l->pHead=pNode;
        l->pTail=pNode;
    }
    else{
        pNode->next=l->pHead;
        l->pHead=pNode;
    }
}
void themVaoCuoi(List* l, Node* pNode){
    if (pNode==NULL) {printf("Thong tin khong the khoi tao.\n");return;}
    if (l->pHead==NULL){
        l->pHead=pNode;
        l->pTail=pNode;
    }
    else{
        l->pTail->next=pNode;
        l->pTail=pNode;
    }
}
void hienThiThongTin1SinhVien(Data sv){
    printf("%35s%10d%10.2f\n",sv.hoTen,sv.tuoi,sv.diemTB);
}
void hienThiDanhSach(List* l){
    printf("\t\tDANH SACH SINH VIEN\n");
    printf("%5s%35s%10s%10s\n","STT","Ho ten","Tuoi","Diem TB");
    if (l->pHead==NULL){
        printf("\tDanh sach trong\n");
    }
    else{
        int stt=1;
        for (Node* i=l->pHead; i!=NULL; i=i->next){
            printf("%5d",stt);stt++;
            hienThiThongTin1SinhVien(i->data);
        }
    }
}
Node* layDiaChiTheoTen(List* l, char tenSV[]){
    Node* i;
    for (i=l->pHead; i!=NULL; i=i->next){
        if (strcmp(i->data.hoTen,tenSV)==0) return i;
    }
    return NULL;
}
int chenThemSinhVien(List* l, char tenSV[]){
    Node* vt=layDiaChiTheoTen(l,tenSV);
    if (vt==NULL) return 0;
    printf("Nhap thong tin sinh vien muon them vao danh sach:\n");
    Node* pNode=taoNode(nhapData());
    if (pNode==NULL) {printf("Thong tin khong the khoi tao.\n");return-1;}
    pNode->next=vt->next;
    vt->next=pNode;
    if(vt==l->pTail) l->pTail=pNode;
    return 1;
}
int xoaMotSinhVien(List* l, char tenSV[]){
    Node   *vt=NULL,*vtTruoc=NULL;
    for(vt=l->pHead; vt!=NULL; vt=vt->next){
        if (strcmp(vt->data.hoTen,tenSV)==0) break;
        vtTruoc=vt;
    }
    if (vt==NULL) return 0;
    if (vtTruoc==NULL) {
        if (vt->next==NULL){
            free(l->pHead);
            init(l);
        }
        else {
            Node* pNode=l->pHead;
            free(pNode);
            l->pHead=l->pHead->next;
        }
        return 1;
    }
    vtTruoc->next=vt->next;
    if (vt==l->pTail) l->pTail=vtTruoc;
    free(vt);
    return 1;
}
int suaSinhVien(List* l, char tenSV[]){
    Node* vt=layDiaChiTheoTen(l,tenSV);
    if (vt==NULL) return 0;
    printf("Nhap lai thong tin: \n");
    Data sv=nhapData();
    vt->data=sv;
    return 1;
}
void xoaDanhSach(List* l){
    while (l->pHead!=NULL){
        Node* pNode=l->pHead;
        l->pHead=l->pHead->next;
        free(pNode);
    }
    init(l);
}
void readFromFile(char tenFile[], List* l){
    FILE* f= fopen(tenFile,"rb");
    Data data;
    while (!feof(f)){
        if (fread(&data,sizeof(Data),1,f)!=0){
            themVaoCuoi(l,taoNode(data));
        }
    }
    fclose(f);
}
void saveToFile(char tenFile[], List* l){
    FILE*f= fopen(tenFile,"wb");
    for (Node* i=l->pHead; i!=NULL; i=i->next){
        fwrite(&i->data,sizeof(Data),1,f);
    }
    fclose(f);
}
void hienThiMenu(){
    printf("\t\tMENU\n");
    printf("1. Tao danh sach sinh vien.\n");
    printf("2. Hien thi danh sach sinh vien.\n");
    printf("3. Chen them sinh vien.\n");
    printf("4. Xoa mot sinh vien.\n");
    printf("5. Sua mot sinh vien.\n");
    printf("6. Ket thuc.\n");
}
int main(){
    List l;
    init(&l);
    while (1){
        system("cls");
        hienThiMenu();
        printf("Chon 1 trong nhung options ben tren: ");
        int  chon;
        scanf("%d",&chon);
        switch(chon){
            case 1:{
                xoaDanhSach(&l);
                int stt=1;
                while(1){
                    printf("\tNhap thong tin sinh vien thu %d\n",stt); stt++;
                    themVaoCuoi(&l,taoNode(nhapData()));
                    printf("Nhap tiep bam nut bat ky, dung bam N: ");
                    char tiep=getch();
                    printf("\n");

                    if (tiep=='n' || tiep =='N') break;
                }
                break;
            }
            case 2:{
                hienThiDanhSach(&l);
                printf("Bam bat ky de ve menu.\n");
                getch();
                break;
            }
            case 3:{
                printf("Nhap ten sinh vien muon chen vao sau: ");
                fflush(stdin);
                char ten[30];
                gets(ten);
                int ok=chenThemSinhVien(&l,ten);
                if (ok==0){
                    printf("Khong tim thay sinh vien %s trong danh sach.\n",ten);
                }
                if (ok==1){
                    printf("Them thanh cong.\n");
                }
                printf("Bam bat ky de ve menu.\n");
                getch();
                break;
            }
            case 4:{
                printf("Nhap ten sinh vien muon xoa: ");
                fflush(stdin);
                char ten[30];
                gets(ten);
                if (xoaMotSinhVien(&l,ten)==1){
                    printf("Xoa thanh cong.\n");
                }
                else printf("Khong tim thay sinh vien %s trong danh sach.\n",ten);
                printf("Bam bat ky de ve menu.\n");
                getch();
                break;
            }
            case 5:{
                printf("Nhap ten sinh vien muon sua: ");
                fflush(stdin);
                char ten[30];
                gets(ten);
                if (suaSinhVien(&l,ten)==1){
                    printf("Sua thanh cong.\n");
                }
                else printf("Khong tim thay sinh vien %s trong danh sach.\n",ten);
                printf("Bam bat ky de ve menu.\n");
                getch();
                break;
            }
            case 6:{
                return 0;
            }
            default: {
                printf("Vui long chi nhap tu 1 den 6.\n");
                printf("Bam bat ky de ve menu.\n");
                getch();
            }
        }
    }
    return 0;
}
