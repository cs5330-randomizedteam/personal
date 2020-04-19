// Code generated by protoc-gen-go. DO NOT EDIT.
// source: google/ads/googleads/v1/services/product_bidding_category_constant_service.proto

package services

import (
	context "context"
	fmt "fmt"
	math "math"

	proto "github.com/golang/protobuf/proto"
	resources "google.golang.org/genproto/googleapis/ads/googleads/v1/resources"
	_ "google.golang.org/genproto/googleapis/api/annotations"
	grpc "google.golang.org/grpc"
	codes "google.golang.org/grpc/codes"
	status "google.golang.org/grpc/status"
)

// Reference imports to suppress errors if they are not otherwise used.
var _ = proto.Marshal
var _ = fmt.Errorf
var _ = math.Inf

// This is a compile-time assertion to ensure that this generated file
// is compatible with the proto package it is being compiled against.
// A compilation error at this line likely means your copy of the
// proto package needs to be updated.
const _ = proto.ProtoPackageIsVersion3 // please upgrade the proto package

// Request message for
// [ProductBiddingCategoryService.GetProductBiddingCategory][].
type GetProductBiddingCategoryConstantRequest struct {
	// Resource name of the Product Bidding Category to fetch.
	ResourceName         string   `protobuf:"bytes,1,opt,name=resource_name,json=resourceName,proto3" json:"resource_name,omitempty"`
	XXX_NoUnkeyedLiteral struct{} `json:"-"`
	XXX_unrecognized     []byte   `json:"-"`
	XXX_sizecache        int32    `json:"-"`
}

func (m *GetProductBiddingCategoryConstantRequest) Reset() {
	*m = GetProductBiddingCategoryConstantRequest{}
}
func (m *GetProductBiddingCategoryConstantRequest) String() string { return proto.CompactTextString(m) }
func (*GetProductBiddingCategoryConstantRequest) ProtoMessage()    {}
func (*GetProductBiddingCategoryConstantRequest) Descriptor() ([]byte, []int) {
	return fileDescriptor_db720fb3c3f176ea, []int{0}
}

func (m *GetProductBiddingCategoryConstantRequest) XXX_Unmarshal(b []byte) error {
	return xxx_messageInfo_GetProductBiddingCategoryConstantRequest.Unmarshal(m, b)
}
func (m *GetProductBiddingCategoryConstantRequest) XXX_Marshal(b []byte, deterministic bool) ([]byte, error) {
	return xxx_messageInfo_GetProductBiddingCategoryConstantRequest.Marshal(b, m, deterministic)
}
func (m *GetProductBiddingCategoryConstantRequest) XXX_Merge(src proto.Message) {
	xxx_messageInfo_GetProductBiddingCategoryConstantRequest.Merge(m, src)
}
func (m *GetProductBiddingCategoryConstantRequest) XXX_Size() int {
	return xxx_messageInfo_GetProductBiddingCategoryConstantRequest.Size(m)
}
func (m *GetProductBiddingCategoryConstantRequest) XXX_DiscardUnknown() {
	xxx_messageInfo_GetProductBiddingCategoryConstantRequest.DiscardUnknown(m)
}

var xxx_messageInfo_GetProductBiddingCategoryConstantRequest proto.InternalMessageInfo

func (m *GetProductBiddingCategoryConstantRequest) GetResourceName() string {
	if m != nil {
		return m.ResourceName
	}
	return ""
}

func init() {
	proto.RegisterType((*GetProductBiddingCategoryConstantRequest)(nil), "google.ads.googleads.v1.services.GetProductBiddingCategoryConstantRequest")
}

func init() {
	proto.RegisterFile("google/ads/googleads/v1/services/product_bidding_category_constant_service.proto", fileDescriptor_db720fb3c3f176ea)
}

var fileDescriptor_db720fb3c3f176ea = []byte{
	// 379 bytes of a gzipped FileDescriptorProto
	0x1f, 0x8b, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0xff, 0x8c, 0x92, 0xcf, 0x4a, 0xeb, 0x40,
	0x18, 0xc5, 0x49, 0x2e, 0x5c, 0xb8, 0xe1, 0xde, 0x4d, 0x56, 0x97, 0xe2, 0xa2, 0xd6, 0x0a, 0xa5,
	0x8b, 0x09, 0x51, 0x44, 0x18, 0xe9, 0x22, 0xed, 0xa2, 0xea, 0x42, 0x43, 0x85, 0x2e, 0x24, 0x10,
	0xa6, 0x99, 0x61, 0x08, 0xb4, 0x33, 0x71, 0xbe, 0x69, 0x41, 0xc4, 0x8d, 0x6f, 0x20, 0x2e, 0xdd,
	0xb9, 0xf4, 0x51, 0xdc, 0xfa, 0x0a, 0xae, 0xdc, 0xf9, 0x06, 0x92, 0x4e, 0x26, 0xe0, 0xa2, 0x7f,
	0x76, 0x87, 0xc9, 0xc9, 0xef, 0xcc, 0x77, 0xbe, 0xf1, 0x62, 0x2e, 0x25, 0x9f, 0xb2, 0x80, 0x50,
	0x08, 0x8c, 0x2c, 0xd5, 0x22, 0x0c, 0x80, 0xa9, 0x45, 0x9e, 0x31, 0x08, 0x0a, 0x25, 0xe9, 0x3c,
	0xd3, 0xe9, 0x24, 0xa7, 0x34, 0x17, 0x3c, 0xcd, 0x88, 0x66, 0x5c, 0xaa, 0xdb, 0x34, 0x93, 0x02,
	0x34, 0x11, 0x3a, 0xad, 0xac, 0xa8, 0x50, 0x52, 0x4b, 0xbf, 0x69, 0x30, 0x88, 0x50, 0x40, 0x35,
	0x11, 0x2d, 0x42, 0x64, 0x89, 0x8d, 0xb3, 0x55, 0x99, 0x8a, 0x81, 0x9c, 0xab, 0xad, 0x42, 0x4d,
	0x58, 0x63, 0xc7, 0xa2, 0x8a, 0x3c, 0x20, 0x42, 0x48, 0x4d, 0x74, 0x2e, 0x05, 0x98, 0xaf, 0xad,
	0x4b, 0xaf, 0x33, 0x64, 0x3a, 0x36, 0xac, 0xbe, 0x41, 0x0d, 0x2a, 0xd2, 0xa0, 0x02, 0x8d, 0xd8,
	0xcd, 0x9c, 0x81, 0xf6, 0xf7, 0xbc, 0x7f, 0x36, 0x3e, 0x15, 0x64, 0xc6, 0xfe, 0x3b, 0x4d, 0xa7,
	0xf3, 0x67, 0xf4, 0xd7, 0x1e, 0x5e, 0x90, 0x19, 0x3b, 0x78, 0x76, 0xbd, 0xfd, 0xf5, 0xb8, 0x2b,
	0x33, 0xa4, 0xff, 0xe5, 0x78, 0xbb, 0x1b, 0xb3, 0xfd, 0x73, 0xb4, 0xa9, 0x2c, 0xb4, 0xed, 0x00,
	0x8d, 0x68, 0x25, 0xab, 0xae, 0x15, 0xad, 0x27, 0xb5, 0x7a, 0x0f, 0xef, 0x1f, 0x4f, 0xee, 0xb1,
	0x7f, 0x54, 0x2e, 0xe3, 0xee, 0x47, 0x1d, 0xbd, 0x62, 0xed, 0xaf, 0x10, 0x74, 0xef, 0xfb, 0x8f,
	0xae, 0xd7, 0xce, 0xe4, 0x6c, 0xe3, 0x4c, 0xfd, 0xee, 0x56, 0x1d, 0xc6, 0xe5, 0x0e, 0x63, 0xe7,
	0xfa, 0xb4, 0xe2, 0x71, 0x39, 0x25, 0x82, 0x23, 0xa9, 0x78, 0xc0, 0x99, 0x58, 0x6e, 0xd8, 0x3e,
	0x9f, 0x22, 0x87, 0xd5, 0x2f, 0xf8, 0xc4, 0x8a, 0x17, 0xf7, 0xd7, 0x30, 0x8a, 0x5e, 0xdd, 0xe6,
	0xd0, 0x00, 0x23, 0x0a, 0xc8, 0xc8, 0x52, 0x8d, 0x43, 0x54, 0x05, 0xc3, 0x9b, 0xb5, 0x24, 0x11,
	0x85, 0xa4, 0xb6, 0x24, 0xe3, 0x30, 0xb1, 0x96, 0x4f, 0xb7, 0x6d, 0xce, 0x31, 0x8e, 0x28, 0x60,
	0x5c, 0x9b, 0x30, 0x1e, 0x87, 0x18, 0x5b, 0xdb, 0xe4, 0xf7, 0xf2, 0x9e, 0x87, 0xdf, 0x01, 0x00,
	0x00, 0xff, 0xff, 0x6e, 0x93, 0x85, 0xef, 0x68, 0x03, 0x00, 0x00,
}

// Reference imports to suppress errors if they are not otherwise used.
var _ context.Context
var _ grpc.ClientConn

// This is a compile-time assertion to ensure that this generated file
// is compatible with the grpc package it is being compiled against.
const _ = grpc.SupportPackageIsVersion4

// ProductBiddingCategoryConstantServiceClient is the client API for ProductBiddingCategoryConstantService service.
//
// For semantics around ctx use and closing/ending streaming RPCs, please refer to https://godoc.org/google.golang.org/grpc#ClientConn.NewStream.
type ProductBiddingCategoryConstantServiceClient interface {
	// Returns the requested Product Bidding Category in full detail.
	GetProductBiddingCategoryConstant(ctx context.Context, in *GetProductBiddingCategoryConstantRequest, opts ...grpc.CallOption) (*resources.ProductBiddingCategoryConstant, error)
}

type productBiddingCategoryConstantServiceClient struct {
	cc *grpc.ClientConn
}

func NewProductBiddingCategoryConstantServiceClient(cc *grpc.ClientConn) ProductBiddingCategoryConstantServiceClient {
	return &productBiddingCategoryConstantServiceClient{cc}
}

func (c *productBiddingCategoryConstantServiceClient) GetProductBiddingCategoryConstant(ctx context.Context, in *GetProductBiddingCategoryConstantRequest, opts ...grpc.CallOption) (*resources.ProductBiddingCategoryConstant, error) {
	out := new(resources.ProductBiddingCategoryConstant)
	err := c.cc.Invoke(ctx, "/google.ads.googleads.v1.services.ProductBiddingCategoryConstantService/GetProductBiddingCategoryConstant", in, out, opts...)
	if err != nil {
		return nil, err
	}
	return out, nil
}

// ProductBiddingCategoryConstantServiceServer is the server API for ProductBiddingCategoryConstantService service.
type ProductBiddingCategoryConstantServiceServer interface {
	// Returns the requested Product Bidding Category in full detail.
	GetProductBiddingCategoryConstant(context.Context, *GetProductBiddingCategoryConstantRequest) (*resources.ProductBiddingCategoryConstant, error)
}

// UnimplementedProductBiddingCategoryConstantServiceServer can be embedded to have forward compatible implementations.
type UnimplementedProductBiddingCategoryConstantServiceServer struct {
}

func (*UnimplementedProductBiddingCategoryConstantServiceServer) GetProductBiddingCategoryConstant(ctx context.Context, req *GetProductBiddingCategoryConstantRequest) (*resources.ProductBiddingCategoryConstant, error) {
	return nil, status.Errorf(codes.Unimplemented, "method GetProductBiddingCategoryConstant not implemented")
}

func RegisterProductBiddingCategoryConstantServiceServer(s *grpc.Server, srv ProductBiddingCategoryConstantServiceServer) {
	s.RegisterService(&_ProductBiddingCategoryConstantService_serviceDesc, srv)
}

func _ProductBiddingCategoryConstantService_GetProductBiddingCategoryConstant_Handler(srv interface{}, ctx context.Context, dec func(interface{}) error, interceptor grpc.UnaryServerInterceptor) (interface{}, error) {
	in := new(GetProductBiddingCategoryConstantRequest)
	if err := dec(in); err != nil {
		return nil, err
	}
	if interceptor == nil {
		return srv.(ProductBiddingCategoryConstantServiceServer).GetProductBiddingCategoryConstant(ctx, in)
	}
	info := &grpc.UnaryServerInfo{
		Server:     srv,
		FullMethod: "/google.ads.googleads.v1.services.ProductBiddingCategoryConstantService/GetProductBiddingCategoryConstant",
	}
	handler := func(ctx context.Context, req interface{}) (interface{}, error) {
		return srv.(ProductBiddingCategoryConstantServiceServer).GetProductBiddingCategoryConstant(ctx, req.(*GetProductBiddingCategoryConstantRequest))
	}
	return interceptor(ctx, in, info, handler)
}

var _ProductBiddingCategoryConstantService_serviceDesc = grpc.ServiceDesc{
	ServiceName: "google.ads.googleads.v1.services.ProductBiddingCategoryConstantService",
	HandlerType: (*ProductBiddingCategoryConstantServiceServer)(nil),
	Methods: []grpc.MethodDesc{
		{
			MethodName: "GetProductBiddingCategoryConstant",
			Handler:    _ProductBiddingCategoryConstantService_GetProductBiddingCategoryConstant_Handler,
		},
	},
	Streams:  []grpc.StreamDesc{},
	Metadata: "google/ads/googleads/v1/services/product_bidding_category_constant_service.proto",
}
